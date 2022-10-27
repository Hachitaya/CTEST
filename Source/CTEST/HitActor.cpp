// Fill out your copyright notice in the Description page of Project Settings.


#include "HitActor.h"
#include "Kismet/GameplayStatics.h"
#include "HitActor.h"
#include "MyPawn.h"

// Sets default values
AHitActor::AHitActor()
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

	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);

	this->OnActorHit.AddDynamic(this, &AHitActor::OnHit);
	Mesh->OnComponentHit.AddDynamic(this, &AHitActor::OnComponentHit);


}

// Called when the game starts or when spawned
void AHitActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AHitActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{

	AMyPawn* test = Cast<AMyPawn>(OtherActor);
	if (test)
	{
		OtherActor->TakeDamage(10, FDamageEvent(), NULL, this);
	}

	//if (OtherActor == Cast<AMyPawn>(OtherActor))
	//{
	//	OtherActor->TakeDamage(10, FDamageEvent(), NULL, this);
	//}


	
}


void AHitActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("why"));
}
