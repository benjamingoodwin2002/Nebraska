// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ObjectMacros.h"
#include "Engine/PointLight.h"
#include "Sound/SoundCue.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Nebraska/GrabObject.h"
#include "Nebraska/ExaminationComponent.h"
#include "NebraskaGameInstance.h"
#include "Nebraska/PickUpActor.h"
#include "Nebraska/LevelDoor.h"
#include "NebraskaCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;
class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(config=Game)
class ANebraskaCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* L_MotionController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> UHeadbob;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> URunHeadbob;

	UPROPERTY(EditAnywhere)
	float SprintSpeedMultiply;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bMouseUp = 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bMouseDown = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool CanSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool Landed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool DoOnce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool DoOnce2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float StrafeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* HoldingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UInteractComponent* GrabberClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> PhysicObjectType2;

public:
	ANebraskaCharacter();

	void GlowStick1();

	UFUNCTION(BlueprintImplementableEvent)
	void glowlighton();

	UFUNCTION(BlueprintImplementableEvent)
	void Walk();

	UFUNCTION(BlueprintImplementableEvent)
	void floor();

	UFUNCTION(BlueprintImplementableEvent)
	void SetTimers();

	UFUNCTION(BlueprintImplementableEvent)
	void ClearTimers();

	UFUNCTION(BlueprintImplementableEvent)
	void pickupHudOn();

	UFUNCTION(BlueprintImplementableEvent)
	void pickupHudOff();

	UFUNCTION(BlueprintImplementableEvent)
	void intHudOn();

	UFUNCTION(BlueprintImplementableEvent)
	void intHudOff();

	UFUNCTION(BlueprintImplementableEvent)
	void ExamHudOn();

	UFUNCTION(BlueprintImplementableEvent)
	void ExamHudOff();

	UFUNCTION(BlueprintImplementableEvent)
	void LevelHudOn();

	UFUNCTION(BlueprintImplementableEvent)
	void LevelHudOff();

	UFUNCTION()
	void Grab();

	UFUNCTION()
	void Throw();

	UFUNCTION()
	void ThrowR();

	UFUNCTION()
	void DropDelyEnd();

	UFUNCTION(BlueprintCallable)
	void UseItem(APickUpActor* Item);

	UFUNCTION()
	void OpenDoor();


protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

	UPROPERTY(EditAnywhere)
	class AGrabObject* CurrentItem;

	UPROPERTY(EditAnywhere)
	class UExaminationComponent* ExamComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool NormalHud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanLook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HealthIsFull;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSprinting;

	bool bHoldingItem;
	bool bInspecting;

	float PitchMax;
	float PitchMin;

	float VelocityLength;

	bool notolerance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool PhysicsHandleHolding;

	FVector HoldingComp;
	FRotator LastRotation;

	FVector Start;
	FVector ForwardVector;
	FVector End;

	FHitResult Hit;
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	FTimerHandle DropDely;

	FHitResult Hit2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> ExamObj;

	bool LookinPhys;
	bool LookinExam;
	bool LookinPick;
	bool LookinLevel;

	UPROPERTY(EditAnywhere)
	class UNebraskaGameInstance* Instance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APickUpActor* PickUpClass;

	FHitResult Hit3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> PickObj;

	FHitResult Hit4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> LevelObj;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ALevelDoor* Leveldoor;

	//Inventory Variables
	UPROPERTY(EditAnywhere)
	int32 Capacity;

	bool AddItem(APickUpActor* Item);
	bool RemoveItem(APickUpActor* Item);

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class APickUpActor*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CrowbarUse;

protected:

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void sprint();
	
	UFUNCTION(BlueprintCallable)
	void stopsprinting();

	void Interact();

	void Inspect();
	void InspectR();

	UFUNCTION(BlueprintCallable)
	void ToggleMovement();

	void ToggleItemPickUp();

	void Examin();

	void PickUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* glowstick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

