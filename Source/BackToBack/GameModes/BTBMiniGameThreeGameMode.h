// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameplayGameMode.h"
#include "BTBMiniGameThreeGameMode.generated.h"
class ABTBMotorcycle;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBMiniGameThreeGameMode : public ABTBGameplayGameMode
{
	GENERATED_BODY()
	
public:

protected:
	virtual void BeginPlay() override;

	void SpawnMotorcycle();
	void SetPlayersAsChildOfMotorcycle();
	void AdjustPlayersCameras();
private:


	
public:

protected:
	UPROPERTY(EditDefaultsOnly, Category="Motorcycle")
	TSubclassOf<ABTBMotorcycle> MotorcycleClass;

private:
	TObjectPtr<ABTBMotorcycle> SpawnedVehicle;
	
};
