// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBCollectables.h"
#include "BTBCollectableSpawner.generated.h"

class UBTBObjectPoolComponent;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBCollectableSpawner : public ABTBActor
{
	GENERATED_BODY()

public:
	ABTBCollectableSpawner();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void SpawnItems();
private:

public:
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	TObjectPtr<UCurveFloat> SpawnRateCurveClass;

	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	TSubclassOf<ABTBCollectables> CollectableClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Components")
	TObjectPtr<UBoxComponent> CollisionBox;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	// TObjectPtr<UBTBObjectPoolComponent> ItemPool;
protected:
private:
	FTimerHandle ItemSpawnHandle;
	
};
