// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

//new custom category
DECLARE_LOG_CATEGORY_EXTERN(LogMyActor, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(MyLogActor, Log, All);



UCLASS()
class CTEST_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TimerTest();
	FTimerHandle TimerTestHandle;


};
