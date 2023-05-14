// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBPooledObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, ABTBPooledObject*, PoolActor);
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBPooledObject : public ABTBActor
{
	GENERATED_BODY()

public:

	FOnPooledObjectDespawn OnPooledObjectDespawn;
	
	void DeactivatePooledObject();

	bool IsActive() const
	{
		return bIsActive;
	}

	void SetPooledObjectActive(bool Value);

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

	bool bIsActive;
	
	int32 PoolIndex;

	float LifeSpan = 0.f;

	FTimerHandle LifeSpanTimer;

	
};
