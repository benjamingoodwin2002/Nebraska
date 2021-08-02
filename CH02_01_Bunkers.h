// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "NebraskaCharacter.h"
#include "CH02_01_Bunkers.generated.h"

/**
 * 
 */
UCLASS()
class NEBRASKA_API ACH02_01_Bunkers : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	ACH02_01_Bunkers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	ANebraskaCharacter* FirstPersonPlayer;

	FTimerHandle EndIntro;

	UFUNCTION()
	void EndIntroEnd();
};
