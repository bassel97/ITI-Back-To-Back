// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBEnemySpawner.generated.h"

class UCurveFloat;
class ABTBEnemyCharacter;
class ABTBPlayableCharacter;

/**
 * Our Version of Enemy Spawner
 */
UCLASS()
class BACKTOBACK_API ABTBEnemySpawner : public ABTBActor
{
	GENERATED_BODY()
	
public:
	ABTBEnemySpawner();

protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;

	void SpawnAICharacterAtRandomLocationRelativeToPlayers();
	FVector GetARandomLocationInPlayersRange();
	void UpdateSpawnEnemyEvery();

private:


public:
	FVector Center;		// Is Set by GameplayGameMode

protected:

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UCurveFloat> SpawnRateCurveClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<ABTBEnemyCharacter> EnemyAIClass;

	UPROPERTY(EditAnywhere, Category = "AI")
	float OuterRange;

	UPROPERTY(EditAnywhere, Category = "AI")
	float DistanceFromCenterOfDonutToInnerRange;

	//UPROPERTY(EditDefaultsOnly, Category = "AI")

	float SpawnEnemyEvery;
	FTimerHandle EnemySpawnHandle;
	FTimerHandle UpdateEnemySpawnHandle;
};