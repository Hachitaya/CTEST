// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"
#include <Components/Boxcomponent.h>
#include "HitActor.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SetRootComponent(SpawnBox);
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnActor::TimerCall, 3.f, true, 1.f);
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpawnActor::Spawn()
{

}

void ASpawnActor::TimerCall()
{
	FVector RandomLocation = FMath::RandPointInBox(SpawnBox->Bounds.GetBox());
	GWorld->SpawnActor<AActor>(AHitActor::StaticClass(), RandomLocation, FRotator(0, 0, 0));
}
