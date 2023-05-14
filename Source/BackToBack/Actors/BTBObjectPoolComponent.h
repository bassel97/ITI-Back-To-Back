// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackToBack/Actors/BTBPooledObject.h"
#include "BTBObjectPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BACKTOBACK_API UBTBObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBTBObjectPoolComponent();

	UPROPERTY(EditAnywhere, Category = "Object Pool");
	TSubclassOf<ABTBPooledObject> PooledObjectSubclass;

	UPROPERTY(EditAnywhere, Category = "Object Pool");
	int32 PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Object Pool");
	float PooledObjectLifeSpan = 0.f;

	ABTBPooledObject* SpawnPooledObject(FVector SpawnPosition, FRotator ObjectOrientation);

	UFUNCTION()
		void OnPooledObjectDespawn(ABTBPooledObject* PooledActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitialPooling();

	TArray<ABTBPooledObject*> ObjectPool;
	TArray<int32> SpawnedPoolIndicies;

	
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
