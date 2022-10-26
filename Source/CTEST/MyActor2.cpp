// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor2.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Components/ArrowComponent.h>

// Sets default values
AMyActor2::AMyActor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> M_Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Mesh;

	if (M_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(M_Mesh.Object);
	}
	


}

// Called when the game starts or when spawned
void AMyActor2::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(2);
}

// Called every frame
void AMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(20, 0, 0));
	AddActorLocalRotation(FRotator(0, 0, 5));
}

