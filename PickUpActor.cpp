// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"
#include "GameFramework/Actor.h"
#include "C:\Program Files\Epic Games\UE_4.26\Engine\Source\Runtime\Engine\Classes\Kismet\GameplayStatics.h"

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;

	PickedUp = false;
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpActor::OnPickedUp()
{
	UGameplayStatics::PlaySound2D(MyMesh, PickUpSound);
	MyMesh->DestroyComponent(true);
}

void APickUpActor::Use(ANebraskaCharacter* Character)
{

}

