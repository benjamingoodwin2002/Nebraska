// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Menu.h"
#include "NebraskaCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AMain_Menu::AMain_Menu()
{

}

void AMain_Menu::BeginPlay()
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
