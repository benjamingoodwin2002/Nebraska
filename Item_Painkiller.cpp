// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Painkiller.h"
#include "NebraskaCharacter.h"
#include "Nebraska/NebraskaGameInstance.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Classes\Kismet\GameplayStatics.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Public\TimerManager.h"

void AItem_Painkiller::Use(class ANebraskaCharacter* Character)
{
	if (Character)
	{
		Instance = Cast<UNebraskaGameInstance>(GetGameInstance());
		
		if (!Character->HealthIsFull)
		{
			Instance->HealthInst += 0.25f;
			Character->RemoveItem(this);
			UGameplayStatics::PlaySound2D(this, UseSound);
			Instance->PainkillerCount -= 1;
		}
	}
}

void AItem_Painkiller::PickUpEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Start of Pick Up Event"));
	FirstPersonPlayer = Cast<ANebraskaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Instance = Cast<UNebraskaGameInstance>(GetGameInstance());
	if (!FirstPersonPlayer->HealthIsFull)
	{
		Instance->HealthInst += 0.25f;
		FirstPersonPlayer->RemoveItem(this);
		UGameplayStatics::PlaySound2D(this, UseSound);
		UE_LOG(LogTemp, Warning, TEXT("Ran Pick Up Event"));
	}
	else
	{
		HealthWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), WidgetClass));
		if (!Donce)
		{
			Donce = true;
			HealthWidget->AddToViewport();
			GetWorld()->GetTimerManager().SetTimer(Repeat, this, &AItem_Painkiller::RepeatEnd, 6.0f, false);
			Instance->PainkillerCount += 1;
		}
	}
}

void AItem_Painkiller::RepeatEnd()
{
	Donce = false;
}


