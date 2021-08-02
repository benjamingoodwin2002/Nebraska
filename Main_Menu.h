// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "NebraskaCharacter.h"
#include "Main_Menu.generated.h"

/**
 * 
 */
UCLASS()
class NEBRASKA_API AMain_Menu : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	AMain_Menu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	ANebraskaCharacter* FirstPersonPlayer;
};
