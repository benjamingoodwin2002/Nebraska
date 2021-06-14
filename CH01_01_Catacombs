// Fill out your copyright notice in the Description page of Project Settings.


#include "CH01_01_Catacombs.h"
#include "NebraskaCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Public\TimerManager.h"

ACH01_01_Catacombs::ACH01_01_Catacombs()
{
	
}

void ACH01_01_Catacombs::BeginPlay()
{
	Super::BeginPlay();

	FirstPersonPlayer = Cast<ANebraskaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	UE_LOG(LogTemp, Warning, TEXT("Begin Play Work"));
	if (FirstPersonPlayer && FirstPersonPlayer == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		FirstPersonPlayer->intHudOff();
		FirstPersonPlayer->NormalHud = false;
		FirstPersonPlayer->bCanLook = false;
		FirstPersonPlayer->bCanMove = false;
		FirstPersonPlayer->FirstPersonCameraComponent->bUsePawnControlRotation = false;
		FirstPersonPlayer->bUseControllerRotationYaw = false;
	}
	GetWorld()->GetTimerManager().SetTimer(EndIntro, this, &ACH01_01_Catacombs::EndIntroEnd, 10.0f, false);
}

void ACH01_01_Catacombs::EndIntroEnd()
{
	if (FirstPersonPlayer && FirstPersonPlayer == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		FirstPersonPlayer->intHudOff();
		FirstPersonPlayer->NormalHud = true;
		FirstPersonPlayer->bCanLook = true;
		FirstPersonPlayer->bCanMove = true;
		FirstPersonPlayer->FirstPersonCameraComponent->bUsePawnControlRotation = true;
		FirstPersonPlayer->bUseControllerRotationYaw = true;
	}
}
