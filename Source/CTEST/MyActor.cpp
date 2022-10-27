// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"


DEFINE_LOG_CATEGORY(LogMyActor)
DEFINE_LOG_CATEGORY(MyLogActor)

// Sets default values
AMyActor::AMyActor() 
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

	ConstructorHelpers::FObjectFinder<UMaterial> M_Mat(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"));
	
	if (M_Mat.Succeeded())
	{
		Mesh->SetMaterial(0, M_Mat.Object);
	}

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerTestHandle, this, &AMyActor::TimerTest, 3.f, true);

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(0, 0, 1));
	//UE_LOG(LogActor, Warning, TEXT("MyActor Tick"));
	//UE_LOG(MyLogActor, Display, TEXT("Custom Log"));

	
}

void AMyActor::TimerTest()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("TimerTest"));
	UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, this->GetActorTransform());

	Destroy();
}

