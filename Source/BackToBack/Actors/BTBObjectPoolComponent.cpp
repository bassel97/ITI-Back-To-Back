// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBObjectPoolComponent.h"
#include "BackToBack/Actors/BTBPooledObject.h"

UBTBObjectPoolComponent::UBTBObjectPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
void UBTBObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialPooling();
	ObjectPool.SetNum(PoolSize, false);
}

void UBTBObjectPoolComponent::InitialPooling()
{
	if(PooledObjectSubclass)
	{
		if(UWorld* const World = GetWorld())
		{
			for(int32 i = 0; i < PoolSize; i++)
			{
				if(ABTBPooledObject* PooledActor = World->SpawnActor<ABTBPooledObject>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator))
				{
					PooledActor->SetPooledObjectActive(false);
					PooledActor->SetPoolIndex(i);
					PooledActor->OnPooledObjectDespawn.AddDynamic(this, &UBTBObjectPoolComponent::OnPooledObjectDespawn);
					ObjectPool.Add(PooledActor);
				}
			}
		}
	}
}

ABTBPooledObject* UBTBObjectPoolComponent::SpawnPooledObject(FVector SpawnPosition, FRotator ObjectOrientation)
{
	if(ObjectPool.IsEmpty())
	{
		return nullptr;
	}
	
	for (ABTBPooledObject* PooledObject : ObjectPool)
	{
		if(PooledObject && !PooledObject->IsActive())
		{
			PooledObject->SetActorLocationAndRotation(SpawnPosition, ObjectOrientation);
			PooledObject->SetPooledObjectLifeSpan(PooledObjectLifeSpan);
			PooledObject->SetPooledObjectActive(true);
			SpawnedPoolIndicies.Add(PooledObject->GetPoolIndex());

			return  PooledObject;
		}
	}
	if(SpawnedPoolIndicies.Num() > 0)
	{
		const int PooledObjectIndex = SpawnedPoolIndicies[0];
		SpawnedPoolIndicies.Remove(PooledObjectIndex);
		ABTBPooledObject* PooledObject = ObjectPool[PooledObjectIndex];

		if(PooledObject)
		{
			PooledObject->SetPooledObjectActive(false);

			PooledObject->SetActorLocationAndRotation(SpawnPosition, ObjectOrientation);
			PooledObject->SetPooledObjectLifeSpan(PooledObjectLifeSpan);
			PooledObject->SetPooledObjectActive(true);
			SpawnedPoolIndicies.Add(PooledObject->GetPoolIndex());

			return PooledObject; 
		}
	}
	return nullptr;
}

void UBTBObjectPoolComponent::OnPooledObjectDespawn(ABTBPooledObject* PooledActor)
{
	SpawnedPoolIndicies.Remove(PooledActor->GetPoolIndex());
}


