// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "c:\users\bgpro\documents\unreal projects\nebraska\Source\Nebraska\NebraskaGameInstance.h"
#include "Nebraska/NebraskaCharacter.h"
#include "LevelDoor.generated.h"

UCLASS(Abstract, Blueprintable)
class NEBRASKA_API ALevelDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UFUNCTION()
	virtual void OpenDoor(class ANebraskaCharacter* Character, class UNebraskaGameInstance* Instance);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> FadeHud;

	UPROPERTY(VisibleInstanceOnly)
	class UUserWidget* FadeWidget;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoorBP(class ANebraskaCharacter* Character, class UNebraskaGameInstance* Instance);

};
