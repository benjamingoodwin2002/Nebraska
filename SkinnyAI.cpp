// Fill out your copyright notice in the Description page of Project Settings.


#include "SkinnyAI.h"
#include "Nebraska.h"
#include "AIPatrolController.h"
#include "NebraskaCharacter.h"
#include "NebraskaGameInstance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "kismet/GameplayStatics.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\AIModule\Classes\Perception\AIPerceptionComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASkinnyAI::ASkinnyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.0f);
}

// Called when the game starts or when spawned
void ASkinnyAI::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ASkinnyAI::OnPlayerCaught);
	}
}

// Called every frame
void ASkinnyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkinnyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASkinnyAI::OnPlayerCaught(APawn* Pawn1)
{
	AAIPatrolController* AIController = Cast<AAIPatrolController>(GetController());
	if (AIController)
	{
		if (PawnSensingComp->HasLineOfSightTo(Pawn1))
		{
			AIController->SetPlayerCaught(Pawn1);
		}
		else
		{
			AIController->SetPlayerLost();
		}
	}
}

