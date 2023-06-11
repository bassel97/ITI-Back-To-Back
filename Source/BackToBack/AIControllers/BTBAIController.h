// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BTBAIController.generated.h"

class ABTBPlayableCharacter;

/**
 * Our Version of AIController
 */
UCLASS()
class BACKTOBACK_API ABTBAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void RunTheBehaviourTree();
	void FillPlayerActorsArray();
	void UpdateBlackboardClosestPlayerVariable();
	TObjectPtr<AActor> GetClosestPlayer();
	
private:
	
	
	
public:
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "BTB_AI")
	TObjectPtr<UBehaviorTree> AIBehaviorTree;

	TArray<TObjectPtr<AActor>> PlayerActors;
private:
	
};
