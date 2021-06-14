// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "NebraskaCharacter.h"
#include "CH01_01_Catacombs.generated.h"

/**
 * 
 */
UCLASS()
class NEBRASKA_API ACH01_01_Catacombs : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	ACH01_01_Catacombs();
	
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
