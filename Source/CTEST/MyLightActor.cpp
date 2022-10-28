// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLightActor.h"
#include "Components/PointLightComponent.h"

// Sets default values
AMyLightActor::AMyLightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	
	Light->AttachTo(RootComponent);
	Light->SetLightColor(FLinearColor(255, 0, 0));
	Light->SetVisibility(false);

	Light->ComponentTags.Add(FName(TEXT("Light")));
}

// Called when the game starts or when spawned
void AMyLightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyLightActor::TurnOn()
{
	Light->SetVisibility(true);
}

void AMyLightActor::TurnOff()
{
	Light->SetVisibility(false);
}

