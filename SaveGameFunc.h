// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameFunc.generated.h"

/**
 * 
 */
UCLASS()
class NEBRASKA_API USaveGameFunc : public USaveGame
{
	GENERATED_BODY()

public:

	USaveGameFunc();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LevelToLoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Load10;
};
