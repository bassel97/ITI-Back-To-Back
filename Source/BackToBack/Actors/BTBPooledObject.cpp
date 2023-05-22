// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPooledObject.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


ABTBPooledObject::ABTBPooledObject()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
}

void ABTBPooledObject::DeactivatePooledObject()
{
	SetPooledObjectActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
}

void ABTBPooledObject::SetPooledObjectActive(const bool Value)
{
	bIsActive = Value;
	SetActorHiddenInGame(!bIsActive);
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &ABTBPooledObject::DeactivatePooledObject, LifeSpan, false);
}




