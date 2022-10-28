// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefaultPawn.h"

AMyDefaultPawn::AMyDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		m_sphere(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	UStaticMeshComponent* Aim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AimComponent"));

	Aim->SetStaticMesh(m_sphere.Object);
	Aim->SetRelativeLocation(FVector(30, 0, 0));
	Aim->SetRelativeScale3D(FVector(0.01f));

	Aim->AttachTo(RootComponent);



}

void AMyDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Extplosion", IE_Pressed, this, &AMyDefaultPawn::Explosion);
}

void AMyDefaultPawn::Explosion()
{

}
