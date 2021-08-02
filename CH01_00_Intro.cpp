// Fill out your copyright notice in the Description page of Project Settings.


#include "CH01_00_Intro.h"
#include "NebraskaCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ACH01_00_Intro::ACH01_00_Intro()
{

}

void ACH01_00_Intro::BeginPlay()
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
}
