// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Nebraska/PickUpActor.h"
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

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool C1Locked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int	PainkillerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BodyTemp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool billyconv;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class APickUpActor*> ItemsInst;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APickUpActor* PickUpClassInst;
};
