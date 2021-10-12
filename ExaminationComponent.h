// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "ExaminationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEBRASKA_API UExaminationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExaminationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	//UPROPERTY(EditAnywhere)
	//ANebraskaCharacter* FirstPersonPlayer;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Examin2();

	UFUNCTION()
	void Examin2End();

	UPROPERTY(EditAnywhere)
	bool IsExamin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly)
	class UUserWidget* ExamWidget;

};
