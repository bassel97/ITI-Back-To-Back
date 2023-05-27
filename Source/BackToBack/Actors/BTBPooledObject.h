// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBPooledObject.generated.h"

class USceneComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, ABTBPooledObject*, PoolActor);
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBPooledObject : public ABTBActor
{
	GENERATED_BODY()

public:
	ABTBPooledObject();
	
	void DeactivatePooledObject();
	void SetPooledObjectActive(bool Value);

	bool IsActive() const
	{
		return bIsActive;
	}

	void SetPooledObjectLifeSpan(const float Value)
	{
		LifeSpan = Value;
	}

	int32 GetPoolIndex() const
	{
		return PoolIndex;
	}

	void SetPoolIndex(const int32 Value)
	{
		PoolIndex = Value;
	}
	
protected:
	
private:

	

public:
	FOnPooledObjectDespawn OnPooledObjectDespawn;
	
protected:
	bool bIsActive;
	int32 PoolIndex;
	float LifeSpan;
	FTimerHandle LifeSpanTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

private:
	
};
