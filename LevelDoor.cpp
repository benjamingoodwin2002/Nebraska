// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDoor.h"
#include "Nebraska/NebraskaCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelDoor::ALevelDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

}

// Called when the game starts or when spawned
void ALevelDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelDoor::OpenDoor(ANebraskaCharacter* Character, UNebraskaGameInstance* Instance)
{
	//UGameplayStatics::OpenLevel(DoorMesh, LevelName);
}

