// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\AIModule\Classes\BehaviorTree\BehaviorTreeComponent.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class NEBRASKA_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()

	//BehaviorTreeComponent
	UBehaviorTreeComponent* BehaviorComp;

	//BlackBoardComponent
	UBlackboardComponent* BlackBoardComp;

	//Blackboars Keys
	UPROPERTY(EditDefaultsOnly)
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly)
	FName PlayerKey;

	TArray<AActor*> PatrolPoints;

	virtual void OnPossess(APawn* InPawn) override;


public:
	AAIPatrolController();

	UPROPERTY(EditAnywhere)
	int32 currentPatrolPoint = 0;

	void SetPlayerCaught(APawn* Pawn1);

	UFUNCTION(BlueprintCallable)
	void SetPlayerLost();

	FORCEINLINE UBlackboardComponent* GetBlackBoardComp() const { return BlackBoardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
};
