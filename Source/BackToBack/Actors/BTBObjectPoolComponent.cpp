// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBObjectPoolComponent.h"
#include "BackToBack/Actors/BTBPooledObject.h"

// Sets default values for this component's properties
UBTBObjectPoolComponent::UBTBObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
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
		UE_LOG(LogTemp, Warning, TEXT("Pool is Empty"));
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






// Called every frame
//void UBTBObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

