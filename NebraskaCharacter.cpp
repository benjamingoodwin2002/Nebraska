// Copyright Epic Games, Inc. All Rights Reserved.

#include "NebraskaCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/PointLight.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/Actor.h"
#include "Nebraska/ExaminationComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Containers/Array.h"
#include "Nebraska/InteractComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ANebraskaCharacter

ANebraskaCharacter::ANebraskaCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	SprintSpeedMultiply = 2.5f;
	CanSprint = true;
	StrafeSpeed = 2.2f;
	Landed = true;
	DoOnce = true;
	DoOnce2 = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(FirstPersonCameraComponent);

	glowstick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("glowstick"));
	glowstick->SetupAttachment(SpringArm);

	HoldingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingComponent"));
	HoldingComponent->SetupAttachment(SpringArm);

	CurrentItem = NULL;
	bCanMove = true;
	bCanLook = true;
	bInspecting = false;

	LookinPhys = false;
	LookinExam = false;

	NormalHud = true;

	GrabberClass = CreateDefaultSubobject<UInteractComponent>(TEXT("GrabberClass"));

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

}

void ANebraskaCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	PitchMax = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax;
	PitchMin = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin;
}

void ANebraskaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GrabberClass != nullptr)
	{
		GrabberClass->TraceHandleLocation(PhysicsHandle, FirstPersonCameraComponent);
	}

	if (bHoldingItem)
	{
		pickupHudOff();
	}

	Start = FirstPersonCameraComponent->GetComponentLocation();
	ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	End = ((ForwardVector * 250.0f) + Start);

	//Exam Object
	if (GetWorld()->LineTraceSingleByObjectType(Hit2, Start, End, ExamObj))
	{
		if (Hit2.GetActor() != nullptr)
		{
			ExamComp = Hit2.GetActor()->FindComponentByClass<UExaminationComponent>();
			if (ExamComp->IsExamin && ExamComp != nullptr)
			{
				ExamHudOff();
				NormalHud = false;
				LookinExam = true;
			}
			else
			{
				if (LookinPhys == false)
				{
					ExamHudOn();
					NormalHud = true;
					LookinExam = true;
				}
			}
		}
		else
		{
			ExamHudOff();
			LookinExam = false;
		}
	}
	else
	{
		ExamHudOff();
		LookinExam = false;
	}

	//Interact Object

	if (GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, PhysicObjectType2))
	{
		if (Hit.GetActor() != nullptr)
		{
			//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 1, 0, 1);
			if (PhysicsHandle != nullptr && GrabberClass->GetIsObjectHeld() && CurrentItem == nullptr)
			{
				intHudOff();
				NormalHud = false;
				LookinPhys = true;
			}
			else
			{
				if (LookinExam == false)
				{
					intHudOn();
					NormalHud = true;
					LookinPhys = true;
				}
			}
		}
		else
		{
			intHudOff();
			LookinPhys = false;
		}
	}
	else
	{
		intHudOff();
		LookinPhys = false;
		if (Hit.GetActor() == nullptr && GrabberClass->bObjectHeld && GrabberClass->bPhysicHandleActive)
		{
			if (DoOnce2)
			{
				UE_LOG(LogTemp, Warning, TEXT("Setting timer"));
				GetWorld()->GetTimerManager().SetTimer(DropDely, this, &ANebraskaCharacter::DropDelyEnd, 1.0f, false);
				DoOnce2 = false;
			}
		}
	}

	//PickUp Object

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	if (!bHoldingItem)
	{
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, DefaultComponentQueryParams, DefaultResponseParam))
		{
			if (Hit.GetActor()->GetClass()->IsChildOf(AGrabObject::StaticClass()))
			{
				pickupHudOn();
				CurrentItem = Cast<AGrabObject>(Hit.GetActor());
			}
			else
			{
				pickupHudOff();
			}
		}
		else
		{
			pickupHudOff();
			CurrentItem = NULL;
		}
	}

	if (bInspecting)
	{
		if (bHoldingItem)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = 179.9000002f;
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = -179.9000002f;
			CurrentItem->RotateObject();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANebraskaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ANebraskaCharacter::sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ANebraskaCharacter::stopsprinting);

	PlayerInputComponent->BindAction("GlowStick", IE_Pressed, this, &ANebraskaCharacter::GlowStick1);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ANebraskaCharacter::Grab);

	PlayerInputComponent->BindAction("Throwing", IE_Pressed, this, &ANebraskaCharacter::Throw);
	PlayerInputComponent->BindAction("Throwing", IE_Released, this, &ANebraskaCharacter::ThrowR);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ANebraskaCharacter::Examin);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ANebraskaCharacter::Interact);

	PlayerInputComponent->BindAction("Inspect", IE_Pressed, this, &ANebraskaCharacter::Inspect);
	PlayerInputComponent->BindAction("Inspect", IE_Released, this, &ANebraskaCharacter::InspectR);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ANebraskaCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ANebraskaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANebraskaCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ANebraskaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ANebraskaCharacter::LookUpAtRate);
}

void ANebraskaCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void ANebraskaCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void ANebraskaCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && bCanMove)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
		if (Value < 0.0f || Value > 0.0f)
		{
			if (Landed == true)
			{
				SetTimers();
			}
		}
		else if (Value == 0.0f)
		{
			ClearTimers();
		}

		if (GetCharacterMovement()->MaxWalkSpeed >= 301.0f)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(URunHeadbob, 1);
		}
		else
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(UHeadbob, 1);
		}
	}
}

void ANebraskaCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && bCanMove)
	{
		if (Value < 0.0f || Value > 0.0f)
		{
			if (Landed == true)
			{
				SetTimers();
			}
		}
		else if (Value == 0.0f)
		{
			ClearTimers();
		}
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(UHeadbob, 1);
	}
}

void ANebraskaCharacter::TurnAtRate(float Rate)
{
	if (bCanLook)
	{
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ANebraskaCharacter::LookUpAtRate(float Rate)
{
	if (bCanLook)
	{
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ANebraskaCharacter::sprint()
{
	if (CanSprint == true && GetCharacterMovement()->MaxWalkSpeed > 299.9 && bCanMove)
	{
		if (DoOnce == true)
		{
			GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiply;
			DoOnce = false;
		}
	}
}

void ANebraskaCharacter::stopsprinting()
{
	if (CanSprint == true)
	{
		if (DoOnce == false)
		{
			GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiply;
			DoOnce = true;
		}
	}
}

void ANebraskaCharacter::Interact()
{
	if (CurrentItem && !bInspecting)
	{
		ToggleItemPickUp();
	}
}

void ANebraskaCharacter::Inspect()
{
	if (bHoldingItem)
	{
		LastRotation = GetControlRotation();
		ToggleMovement();
	}
	else
	{
		bInspecting = true;
	}
}

void ANebraskaCharacter::InspectR()
{
	if (bInspecting && bHoldingItem)
	{
		GetController()->SetControlRotation(LastRotation);
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = PitchMax;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = PitchMin;
		ToggleMovement();
	}
	else
	{
		bInspecting = false;
	}
}

void ANebraskaCharacter::ToggleMovement()
{
	bCanMove = !bCanMove;
	bInspecting = !bInspecting;
	FirstPersonCameraComponent->bUsePawnControlRotation = !FirstPersonCameraComponent->bUsePawnControlRotation;
	bUseControllerRotationYaw = !bUseControllerRotationYaw;
}

void ANebraskaCharacter::ToggleItemPickUp()
{
	if (CurrentItem)
	{
		bHoldingItem = !bHoldingItem;
		CurrentItem->PickUpObject();

		if (!bHoldingItem)
		{
			CurrentItem = NULL;
		}
	}
}

void ANebraskaCharacter::Examin()
{
	if (Hit2.GetActor() != nullptr && LookinExam)
	{
		if (ExamComp->IsExamin)
		{
			ToggleMovement();
			ExamHudOff();
			NormalHud = true;
			ExamComp->Examin2End();
		}
		else
		{
			ToggleMovement();
			ExamHudOff();
			NormalHud = false;
			ExamComp->Examin2();
			if (GrabberClass->GetIsObjectHeld())
			{
				GrabberClass->Release(PhysicsHandle);
			}
		}
	}
}

void ANebraskaCharacter::GlowStick1()
{
	if (bCanMove)
	{
		glowstick->ToggleVisibility(true);
		glowlighton();
	}
}

void ANebraskaCharacter::Grab()
{
	if (GrabberClass != nullptr && CurrentItem == nullptr && LookinExam == false)
	{
		switch (GrabberClass->GetIsObjectHeld())
		{
			case true:
			{
				if (PhysicsHandle != nullptr)
				{
					if (GrabberClass->Release(PhysicsHandle))
					{
						UE_LOG(LogTemp, Warning, TEXT("Released"));
						NormalHud = true;
						LookinPhys = false;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Faliure to release"));
					}
				}
				break;
			}
			case false:
			{
				if (PhysicsHandle != nullptr && FirstPersonCameraComponent != nullptr)
				{
					if (GrabberClass->Grab(this, PhysicsHandle, FirstPersonCameraComponent))
					{
						UE_LOG(LogTemp, Warning, TEXT("Grabbed"));
						NormalHud = false;
						LookinPhys = true;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Faliure to grab"));
					}
				}
				break;
			}
		}
	}
}

void ANebraskaCharacter::Throw()
{
	bMouseDown = true;
	bMouseUp = false;
	if (GrabberClass != nullptr)
	{
		if (PhysicsHandle != nullptr && FirstPersonCameraComponent != nullptr)
		{
			if (GrabberClass->GetIsObjectHeld())
			{
				if (GrabberClass->Throw(PhysicsHandle, FirstPersonCameraComponent, bMouseDown))
				{
					UE_LOG(LogTemp, Warning, TEXT("Throw"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("failure to throw"));
				}
			}
		}
	}
}

void ANebraskaCharacter::ThrowR()
{
	bMouseUp = true;
	bMouseDown = false;
}

void ANebraskaCharacter::DropDelyEnd()
{
	if (Hit.GetActor() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Timer Active"));
		GrabberClass->Release(PhysicsHandle);
		DoOnce2 = true;
		NormalHud = true;
		intHudOff();
		LookinPhys = false;
		UE_LOG(LogTemp, Warning, TEXT("Timer Success"));
	}
	else
	{
		DoOnce2 = true;
	}
}
