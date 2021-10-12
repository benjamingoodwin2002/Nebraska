// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPatrolPoint.h"
#include "Nebraska.h"
#include "AIPatrolPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AIcon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	if (AIcon)
	{
		UBlackboardComponent* BlackboardComp = AIcon->GetBlackBoardComp();

		AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailablePatrolPoints = AIcon->GetPatrolPoints();

		AAIPatrolPoint* NextPatrolPoint = nullptr;

		if (AIcon->currentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[++AIcon->currentPatrolPoint]);
		}
		else
		{
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);
			AIcon->currentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
