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
	
private:
	
	
	
public:
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "BTB_AI")
	TObjectPtr<UBehaviorTree> AIBehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "BTB_AI")
	TSubclassOf<ABTBPlayableCharacter> PlayableCharacter;
private:
	
};
