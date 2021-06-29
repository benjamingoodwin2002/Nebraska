// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NebraskaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEBRASKA_API UNebraskaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UNebraskaGameInstance();
	bool C1Locked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthInst;
};
