// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPooledObject.h"



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




