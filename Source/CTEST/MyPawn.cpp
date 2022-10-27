// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "MyActor.h"
#include "MyActor2.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "TimerTest.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> M_Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Mesh;

	if (M_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(M_Mesh.Object);
	} 

	USpringArmComponent* CameraArm = CreateDefaultSubobject<USpringArmComponent>
		(TEXT("CameraSpringArm"));
	CameraArm->AttachTo(Mesh);
	CameraArm->SetRelativeLocationAndRotation(FVector(0, 0, 50.f), FRotator(-60.f, 0, 0));
	CameraArm->TargetArmLength = 400.f;
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 3.f;
	CameraArm->bDoCollisionTest = false;
	
	UCameraComponent* FollowCamera =
		CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	FollowCamera->AttachTo(CameraArm);

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime
)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);
	
	PlayerInputComponent->BindAction("AddSphere", IE_Pressed, this, &AMyPawn::AddSphere);
	PlayerInputComponent->BindAction("SpawnActor", IE_Pressed, this, &AMyPawn::SpawnMyActor);
	PlayerInputComponent->BindAction("SpawnActor2", IE_Pressed, this, &AMyPawn::SpawnMyActor2);
	PlayerInputComponent->BindAction("Explosion", IE_Pressed, this, &AMyPawn::Explosion);
	PlayerInputComponent->BindAction("SpawnTimer", IE_Pressed, this, &AMyPawn::SpawnTimer);
}

void AMyPawn::MoveForward(float Value)
{
	AddActorWorldOffset(FVector(Value, 0, 0));
} 

void AMyPawn::MoveRight(float Value)
{
	AddActorWorldOffset(FVector(0, Value, 0));
}

void AMyPawn::AddSphere()
{
	UStaticMeshComponent* NewSphere = NewObject<UStaticMeshComponent>(this,
		UStaticMeshComponent::StaticClass(), FName("AddSphere"));
	if (NewSphere)
	{                 
		UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
		UMaterial* mat = LoadObject<UMaterial>(nullptr, TEXT("MMaterial'/Game/StarterContent/Materials/M_AssetPlatform.M_AssetPlatform'"));

		NewSphere->AttachTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
		NewSphere->SetRelativeLocation(FVector(0, 0, 100));
		NewSphere->SetMaterial(0, mat);
		NewSphere->SetStaticMesh(mesh);
		NewSphere->RegisterComponent();
	}
}

void AMyPawn::SpawnMyActor()
{
	//FActorSpawnParameters()

	GetWorld()->SpawnActor<AActor>(AMyActor::StaticClass(), K2_GetActorLocation(), K2_GetActorRotation());
}

void AMyPawn::SpawnMyActor2()
{
	GetWorld()->SpawnActor<AActor>(AMyActor2::StaticClass(), K2_GetActorLocation(), K2_GetActorRotation());
	
}

void AMyPawn::Explosion()
{

	UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));


	for (TActorIterator<AMyActor> actor(GetWorld()); actor; ++actor)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor->GetActorTransform());
		actor->Destroy();  
	}
	for (AMyActor2* actor2 : TActorRange<AMyActor2>(GetWorld()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor2->GetActorTransform());
		actor2->Destroy();
	}
}

void AMyPawn::SpawnTimer()
{
	GetWorld()->SpawnActor<AActor>(ATimerTest::StaticClass(), K2_GetActorLocation(), K2_GetActorRotation());
}
