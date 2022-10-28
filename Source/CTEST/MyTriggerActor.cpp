// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTriggerActor.h"
#include <Components/BoxComponent.h>
#include "MyDefaultPawn.h"
#include <EngineUtils.h>
#include "MyLightActor.h"
#include <Kismet/GameplayStatics.h>
#include <Components/PointLightComponent.h>

// Sets default values
AMyTriggerActor::AMyTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));

	Box->AttachTo(RootComponent);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AMyTriggerActor::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &AMyTriggerActor::OnOvelapEnd);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	Light->SetLightColor(FLinearColor(0, 0, 255));
	Light->SetVisibility(false);

	Light->AttachTo(Box);

}

// Called when the game starts or when spawned
void AMyTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<AMyDefaultPawn>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("why"));

		for (AActor* actors : TActorRange<AActor>(GWorld))
		{
			if (actors == Cast<AMyLightActor>(actors))
			{
				AMyLightActor* actorfind = Cast<AMyLightActor>(actors);
				actorfind->TurnOn();
			}
		}
		Light->SetVisibility(true);

	}
}

void AMyTriggerActor::OnOvelapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Cast<AMyDefaultPawn>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("why"));

		for (AActor* actors : TActorRange<AActor>(GWorld))
		{
			if (actors == Cast<AMyLightActor>(actors))
			{
				AMyLightActor* actorfind = Cast<AMyLightActor>(actors);
				actorfind->TurnOff();
			}
		}
	}
	Light->SetVisibility(false);
}

