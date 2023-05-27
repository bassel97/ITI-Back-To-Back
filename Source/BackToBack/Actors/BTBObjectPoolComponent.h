// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BTBObjectPoolComponent.generated.h"

class ABTBPooledObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BACKTOBACK_API UBTBObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UBTBObjectPoolComponent();

	ABTBPooledObject* SpawnPooledObject(FVector SpawnPosition, FRotator ObjectOrientation);

	UFUNCTION()
	void OnPooledObjectDespawn(ABTBPooledObject* PooledActor);
	
protected:
	virtual void BeginPlay() override;

	void InitialPooling();
	
private:


	
public:
	UPROPERTY(EditAnywhere, Category = "Object Pool");
	TSubclassOf<ABTBPooledObject> PooledObjectSubclass;

	UPROPERTY(EditAnywhere, Category = "Object Pool");
	int32 PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Object Pool");
	float PooledObjectLifeSpan;
	
protected:
	TArray<TObjectPtr<ABTBPooledObject>> ObjectPool;
	TArray<int32> SpawnedPoolIndicies;
	
private:
	
};
