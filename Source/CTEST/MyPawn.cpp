// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> M_Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
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
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

