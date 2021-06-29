// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpActor.h"
#include "Nebraska/NebraskaGameInstance.h"
#include "Item_Painkiller.generated.h"

/**
 * 
 */
UCLASS()
class NEBRASKA_API AItem_Painkiller : public APickUpActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	class USoundBase* UseSound;

	UPROPERTY(EditAnywhere)
	class UNebraskaGameInstance* Instance;

	virtual void Use(class ANebraskaCharacter* Character) override;
};
