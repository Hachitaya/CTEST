// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerTest.h"
#include <Components/TextRenderComponent.h>

// Sets default values
ATimerTest::ATimerTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.f);
	RootComponent = CountdownText;

	CountdownTime = 3;
	CountdownText->SetText(FString::FromInt(CountdownTime));
	


}

// Called when the game starts or when spawned
void ATimerTest::BeginPlay()
{
	Super::BeginPlay();


	GetWorldTimerManager().SetTimer(TimerTestHandle, this, &ATimerTest::TimerPractice, 1.f, true, 0.f);



}

// Called every frame
void ATimerTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimerTest::TimerPractice()
{

	CountdownText->SetText(FString::FromInt(CountdownTime));
	--CountdownTime;
	if (CountdownTime<0)
	{
		CountdownText->SetText(TEXT("Go!"));
		GetWorldTimerManager().ClearTimer(TimerTestHandle);
	}
}

