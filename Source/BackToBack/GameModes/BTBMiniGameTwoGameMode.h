// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameplayGameMode.h"
#include "BTBMiniGameTwoGameMode.generated.h"

class ABTBSpear;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBMiniGameTwoGameMode : public ABTBGameplayGameMode
{
	GENERATED_BODY()
	
public:

protected:
	virtual void BeginPlay() override;
	void AssignSpearToPlayer();
	void SetTopDownCameraReferenceForEachPlayer();

private:


public:

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Player Weapons")
		TSubclassOf<ABTBSpear> SpearClass;

	TObjectPtr<ABTBSpear> SpearPtr;

private:
};
