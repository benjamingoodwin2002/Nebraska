// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Painkiller.h"
#include "NebraskaCharacter.h"
#include "Nebraska/NebraskaGameInstance.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Classes\Kismet\GameplayStatics.h"

void AItem_Painkiller::Use(class ANebraskaCharacter* Character)
{
	if (Character)
	{
		Instance = Cast<UNebraskaGameInstance>(GetGameInstance());
		
		Instance->HealthInst += 0.25f;
		Character->RemoveItem(this);
		UGameplayStatics::PlaySound2D(this, UseSound);
	}
}
