// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkinnyAI.generated.h"

UCLASS()
class NEBRASKA_API ASkinnyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkinnyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
	class UNebraskaGameInstance* Instance;

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComp;

private:

	UFUNCTION()
	void OnPlayerCaught(APawn* Pawn1);
};
