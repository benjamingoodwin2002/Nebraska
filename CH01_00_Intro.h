// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "NebraskaCharacter.h"
#include "CH01_00_Intro.generated.h"

/**
 * 
 */
UCLASS()
class NEBRASKA_API ACH01_00_Intro : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	ACH01_00_Intro();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	ANebraskaCharacter* FirstPersonPlayer;
	
};
