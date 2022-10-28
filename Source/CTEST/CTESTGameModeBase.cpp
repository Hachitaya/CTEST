// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTESTGameModeBase.h"
#include "MyPawn.h"
#include "MyActor.h"
#include "MyDefaultPawn.h"

ACTESTGameModeBase::ACTESTGameModeBase()
{
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}

void ACTESTGameModeBase::BeginPlay()
{
	AMyActor* ActorPtr = NewObject<AMyActor>(this, TEXT("TestUObject"));
	UObject* ObjPtr = ActorPtr;
	UClass* MyActorClass = AMyActor::StaticClass();
	UClass* ObjectClass = UObject::StaticClass();
	UClass* ActorPtrClass = ActorPtr->GetClass();
	UClass* ObjectPtrClass = ObjPtr->GetClass();

	UE_LOG(LogClass, Error, TEXT("Name : %s"), *MyActorClass->GetName());
	UE_LOG(LogClass, Error, TEXT("Name : %s"), *ObjectClass->GetName());
	UE_LOG(LogClass, Error, TEXT("Name : %s"), *ActorPtrClass->GetName());
	UE_LOG(LogClass, Error, TEXT("Name : %s"), *ObjectPtrClass->GetName());


}
