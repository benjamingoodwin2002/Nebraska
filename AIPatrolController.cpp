// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrolController.h"
#include "NebraskaCharacter.h"
#include "SkinnyAI.h"
#include "Nebraska.h"
#include "AICONTROLLER.H"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIPatrolController::OnPossess(APawn* InPawn)
{

	Super::OnPossess(InPawn);

	ASkinnyAI* AICharacter = Cast<ASkinnyAI>(InPawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackBoardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
		// Populazie Patrol Point array
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}
}

AAIPatrolController::AAIPatrolController()
{
	// Initliaze blackboard and behavior tree
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Comp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Comp"));

	//Initalize Blackboard Keys
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";

	currentPatrolPoint = 0;
}

void AAIPatrolController::SetPlayerCaught(APawn* Pawn1)
{
	if (BlackBoardComp)
	{
		BlackBoardComp->SetValueAsObject(PlayerKey, Pawn1);
	}
}

void AAIPatrolController::SetPlayerLost()
{
	if (BlackBoardComp)
	{
		//BlackBoardComp->SetValueAsObject(PlayerKey, nullptr);
		BlackBoardComp->ClearValue(PlayerKey);
		BlackBoardComp->SetValueAsObject(PlayerKey, NULL);
	}
}
