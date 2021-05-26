// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GrabObject.generated.h"

UCLASS()
class NEBRASKA_API AGrabObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PickUpObject();

	UFUNCTION()
	void RotateObject();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComp;

	bool bHolding;
	bool bGravity;

	FRotator ControlRotation;
	ACharacter* MyCharacter;
	UCameraComponent* PlayerCamera;
	FVector ForwardVector;

};
