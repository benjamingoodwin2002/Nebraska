// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/Object.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEBRASKA_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//PhysicHandles Origin
	UPROPERTY(VisibleAnywhere)
	FVector HandleLocation;
	
	//Array For Physic Objects
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> PhysicObjectType;

	//Actors To Ignore
	UPROPERTY(EditAnywhere)
	TArray <AActor*> ActorsToIgnore;

	//cached referenced to the hit component
	UPROPERTY(EditAnywhere)
	UPrimitiveComponent* HitComp;

	//Sound that plays when grabbing an object
	UPROPERTY(EditAnywhere)
	class USoundBase* GrabSound;

	//Checks whether something is being held
	UPROPERTY(VisibleAnywhere)
	bool bObjectHeld;

	//Checks whether physic handle is active
	UPROPERTY(EditAnywhere)
	bool bPhysicHandleActive;

	//Distance to Pick Up
	UPROPERTY(EditAnywhere)
	float MinGrabLength = 1000.0f;

	//Max Distance to Pick Up
	UPROPERTY(EditAnywhere)
	float RayLength = 300.0f;

	//Distance between the player and the diserable pick up length
	UPROPERTY(VisibleAnywhere)
	float VectorLength = 1.0f;

	UPROPERTY(EditAnywhere)
	float ThrowForce = 1000.0f;

	//Weight Limit
	UPROPERTY(EditAnywhere)
	float ObjWeightLimit = 500.0f;

	//snap distance
	UPROPERTY(EditAnywhere)
	float SnapDistance = 450.0f;


	bool Grab(class UObject* WorldContextObject, class UPhysicsHandleComponent* PH, class UCameraComponent* FirstPersonCamera);
	bool Throw(class UPhysicsHandleComponent* PH, class UCameraComponent* FirstPersonCamera, bool MouseDown);
	bool Release(class UPhysicsHandleComponent* PH);

	void TraceHandleLocation(class UPhysicsHandleComponent* PH, class UCameraComponent* FirstPersonCamera);

	FORCEINLINE bool GetIsObjectHeld() const { return bObjectHeld; }
};
