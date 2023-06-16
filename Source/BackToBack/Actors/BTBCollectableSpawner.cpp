// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCollectableSpawner.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABTBCollectableSpawner::ABTBCollectableSpawner()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Box"));
	CollisionBox->SetupAttachment(RootComponent);

}

void ABTBCollectableSpawner::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}

	World->GetTimerManager().SetTimer
(
	ItemSpawnHandle,
	this,
	&ABTBCollectableSpawner::SpawnItems,
	/*0.25f*/ 60,
	true
);
}

void ABTBCollectableSpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ABTBCollectableSpawner::SpawnItems()
{
	const TObjectPtr<UWorld> World = GetWorld();

	if(!ensure(World != nullptr))
	{
		return;
	}

	if(!ensure(CollectableClass != nullptr))
	{
		return;
	}
	
	FVector BoxExtent = CollisionBox->GetScaledBoxExtent();
	FVector BoxLocation = CollisionBox->GetRelativeLocation();

	FVector randPoint =  UKismetMathLibrary::RandomPointInBoundingBox(BoxLocation,BoxExtent);

	const TObjectPtr<ABTBCollectables> SpawnedItem =
	World->SpawnActor<ABTBCollectables>(CollectableClass, randPoint, FRotator::ZeroRotator);
	
	
}
