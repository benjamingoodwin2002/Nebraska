// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Classes\PhysicsEngine\PhysicsHandleComponent.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Classes\GameFramework\Actor.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Classes\Kismet\KismetSystemLibrary.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Classes\Kismet\GameplayStatics.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInteractComponent::Grab(UObject* WorldContextObject, UPhysicsHandleComponent* PH, UCameraComponent* FirstPersonCamera)
{
	if (FirstPersonCamera == nullptr || WorldContextObject == nullptr) return false;

	FHitResult Hit;
	FVector StartTrace = FirstPersonCamera->GetComponentLocation();
	FVector ForwardVector = FirstPersonCamera->GetForwardVector();
	FVector EndTrace = ((ForwardVector * RayLength) + StartTrace);
	FVector MyLocation = GetOwner()->GetActorLocation();
	FRotator MyRotation = GetOwner()->GetActorRotation();
	FTransform Mytransforms = GetOwner()->GetActorTransform();

	if (UKismetSystemLibrary::LineTraceSingleForObjects(WorldContextObject, StartTrace, EndTrace, PhysicObjectType, false, ActorsToIgnore, EDrawDebugTrace::None, Hit, true, FColor::Red, FColor::Green))
	{
		if (Hit.GetActor() != nullptr)
		{
			HitComp = Hit.GetComponent();
			if (HitComp != nullptr)
			{
				if (HitComp->IsSimulatingPhysics())
				{
					if (HitComp->GetMass() < ObjWeightLimit)
					{
						FVector Distance = HitComp->GetComponentLocation(); //MyLocation -
						VectorLength = Distance.Size();
						if (PH != nullptr)
						{
							HitComp->SetEnableGravity(true);
							bPhysicHandleActive = true;
							VectorLength = SnapDistance;
							bObjectHeld = true;
							ObjectHeldBP = true;
							if (GrabSound != nullptr)
							{
								UGameplayStatics::PlaySoundAtLocation(this, GrabSound, GetOwner()->GetActorLocation());
							}
							PH->GrabComponent(HitComp, Hit.BoneName, HitComp->GetCenterOfMass(), true);
							return true;
						}
						else return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

bool UInteractComponent::Throw(UPhysicsHandleComponent* PH, UCameraComponent* FirstPersonCamera, bool MouseDown)
{
	if (FirstPersonCamera != nullptr)
	{
		if (Release(PH))
		{
			if (HitComp != nullptr)
			{
				if (MouseDown && HitComp->IsSimulatingPhysics())
				{
					const FVector StartTrace = FirstPersonCamera->GetComponentLocation();
					const FVector ForwardVector = FirstPersonCamera->GetForwardVector();
					FVector ImpulseVector = ForwardVector * ThrowForce;
					HitComp->AddImpulse(ImpulseVector, NAME_None, true);
				}
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

bool UInteractComponent::Release(UPhysicsHandleComponent* PH)
{
	if (PH != nullptr && bObjectHeld && bPhysicHandleActive)
	{
		bPhysicHandleActive = false;
		bObjectHeld = false;
		ObjectHeldBP = false;
		PH->ReleaseComponent();
		return true;
	}
	else return false;
}

void UInteractComponent::TraceHandleLocation(UPhysicsHandleComponent* PH, UCameraComponent* FirstPersonCamera)
{
	if (bPhysicHandleActive)
	{
		if (PH != NULL && FirstPersonCamera != NULL)
		{
			FVector StartTrace = FirstPersonCamera->GetComponentLocation();
			FVector ForwardVector = FirstPersonCamera->GetForwardVector();
			FVector EndTrace = StartTrace + (ForwardVector * VectorLength);
			HandleLocation = EndTrace;

			PH->SetTargetLocationAndRotation(HandleLocation, GetOwner()->GetActorRotation());
		}
	}
}

