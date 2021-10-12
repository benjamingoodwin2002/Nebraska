// Fill out your copyright notice in the Description page of Project Settings.


#include "NebraskaGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.H"

UNebraskaGameInstance::UNebraskaGameInstance()
{
	C1Locked = true;
	HealthInst = 1.0f;
	BodyTemp = 0.63f;
}

//void UNebraskaGameInstance::Init()
//{
//	UE_LOG(LogTemp, Warning, Text("We are here"), *testwidgetClass->GetName());
//}

//void UNebraskaGameInstance::showwidget()
//{
	//Create WIdget and add it to viewpoint
//	UUserWidget* test = CreateWidget<UUserWidget>(this, testwidgetClass);
//	test->AddToViewport();

//	APlayerController* PlayerController = GetFirstLocalPlayerController();

//}
