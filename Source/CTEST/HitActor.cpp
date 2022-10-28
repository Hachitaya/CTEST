// Fill out your copyright notice in the Description page of Project Settings.


#include "HitActor.h"
#include "Kismet/GameplayStatics.h"
#include "HitActor.h"
#include "MyPawn.h"
#include "GameFramework/DamageType.h"
#include "MyActorComponent.h"


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

	Mesh->SetSimulatePhysics(false);
	Mesh->SetNotifyRigidBodyCollision(true);

	//this->OnActorHit.AddDynamic(this, &AHitActor::OnHit);
	//Mesh->OnComponentHit.AddDynamic(this, &AHitActor::OnComponentHit);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AHitActor::OnOverlapBegin);

	//Mesh->SetGenerateOverlapEvents(true);

	Mesh->SetCollisionObjectType(ECC_WorldDynamic);

	Mesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	UMyActorComponent* Chase = CreateDefaultSubobject<UMyActorComponent>(TEXT("Chase"));

	Chase->ComponentTags.Add(FName(TEXT("Move")));

}

// Called when the game starts or when spawned
void AHitActor::BeginPlay()
{
	Super::BeginPlay();

	for (UActorComponent* actComp : GetComponents())
	{
		if (actComp->ComponentHasTag(FName(TEXT("Move"))))
		{
			UMyActorComponent* myActComp = Cast<UMyActorComponent>(actComp);
			AActor* target = GWorld->GetFirstPlayerController()->GetPawn();
			myActComp->SetFollowTarget(target, 0.5f);
		}
	}
	SetLifeSpan(2);
	
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
		UGameplayStatics::ApplyDamage(OtherActor, 50.f, NULL, this, nullptr);
	}
	if (OtherActor == Cast<AMyPawn>(OtherActor))
	{
		OtherActor->TakeDamage(10, FDamageEvent(), NULL, this);

	}
}


void AHitActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("why"));
}

void AHitActor::OnOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPawn* MyPawn = Cast<AMyPawn>(OtherActor);
	if (MyPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("why"));
	}

}
