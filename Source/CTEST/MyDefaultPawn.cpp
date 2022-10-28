// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefaultPawn.h"
#include "GameFramework/Pawn.h"
#include <Engine/Private/KismetTraceUtils.h>
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

using namespace EDrawDebugTrace;

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
	PlayerInputComponent->BindAction("Explosion", IE_Pressed, this, &AMyDefaultPawn::Explosion);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("MoveForward", this, &AMyDefaultPawn::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &AMyDefaultPawn::MoveRight);
	//PlayerInputComponent->BindAxis("Turn", this, &AMyDefaultPawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &AMyDefaultPawn::AddControllerPitchInput);
}

void AMyDefaultPawn::Explosion()
{
	const FVector Start = GetActorLocation();
	const FVector Direction = GetActorRotation().Vector();
	const FVector End = Start + (Direction * 10000.f);
	//result
	FHitResult Hit;
	//trace parameter
	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
	
	TraceParams.bTraceComplex = true;

	TraceParams.bReturnFaceIndex = false;
	//ignore self
	TraceParams.AddIgnoredActor(this);
	//debug
	FName TraceTag = TEXT("Draw");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	TraceParams.TraceTag = TraceTag;

	EDrawDebugTrace::Type debug = EDrawDebugTrace::Type(ForDuration);

	GWorld->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);

	if (Hit.GetActor())
	{ 
		Hit.GetActor()->TakeDamage(10, FDamageEvent(), NULL, this);
		Hit.GetActor()->Destroy();
	}
	//DrawDebugLineTraceSingle(GWorld, Start, End, debug, 0, Hit, FLinearColor(255,0,0), FLinearColor(0, 0, 255), 10.f);
}
