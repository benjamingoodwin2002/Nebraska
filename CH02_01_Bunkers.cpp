// Fill out your copyright notice in the Description page of Project Settings.


#include "CH02_01_Bunkers.h"
#include "NebraskaCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Public\TimerManager.h"

ACH02_01_Bunkers::ACH02_01_Bunkers()
{

}

void ACH02_01_Bunkers::BeginPlay()
{
	Super::BeginPlay();

	FirstPersonPlayer = Cast<ANebraskaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	UE_LOG(LogTemp, Warning, TEXT("Begin Play Work"));
	if (FirstPersonPlayer && FirstPersonPlayer == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		FirstPersonPlayer->intHudOff();
		FirstPersonPlayer->notolerance = true;
		FirstPersonPlayer->NormalHud = false;
		FirstPersonPlayer->bCanLook = false;
		FirstPersonPlayer->bCanMove = false;
		FirstPersonPlayer->FirstPersonCameraComponent->bUsePawnControlRotation = false;
		FirstPersonPlayer->bUseControllerRotationYaw = false;
	}
	GetWorld()->GetTimerManager().SetTimer(EndIntro, this, &ACH02_01_Bunkers::EndIntroEnd, 9.0f, false);
}

void ACH02_01_Bunkers::EndIntroEnd()
{
	if (FirstPersonPlayer && FirstPersonPlayer == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		FirstPersonPlayer->intHudOff();
		FirstPersonPlayer->notolerance = false;
		FirstPersonPlayer->NormalHud = true;
		FirstPersonPlayer->bCanLook = true;
		FirstPersonPlayer->bCanMove = true;
		FirstPersonPlayer->FirstPersonCameraComponent->bUsePawnControlRotation = true;
		FirstPersonPlayer->bUseControllerRotationYaw = true;
	}
}
