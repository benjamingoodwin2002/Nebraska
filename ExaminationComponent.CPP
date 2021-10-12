// Fill out your copyright notice in the Description page of Project Settings.


#include "ExaminationComponent.h"
#include "NebraskaCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UExaminationComponent::UExaminationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	IsExamin = false;

	// ...
}


// Called when the game starts
void UExaminationComponent::BeginPlay()
{
	Super::BeginPlay();

	//FirstPersonPlayer = Cast<ANebraskaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//if (FirstPersonPlayer && FirstPersonPlayer == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	//{
	//	FirstPersonPlayer->IsExamin = false;
	//}
	// ...
	
}


// Called every frame
void UExaminationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UExaminationComponent::Examin2()
{
	UE_LOG(LogTemp, Warning, TEXT("Examing"));
	IsExamin = true;
	ExamWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), WidgetClass));

	if (ExamWidget != nullptr)
	{
		ExamWidget->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("Examing Success"));
	}
}

void UExaminationComponent::Examin2End()
{
	IsExamin = false;
	if (ExamWidget != nullptr)
	{
		ExamWidget->RemoveFromParent();
	}
}

