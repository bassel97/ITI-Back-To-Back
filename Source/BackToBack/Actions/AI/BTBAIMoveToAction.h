// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBAIMoveToAction.generated.h"

/**
 * Our version of Move action that AI uses to move to a destination,
 * similar to PlayerMoveAction but using AI.
 */
UCLASS()
class BACKTOBACK_API UBTBAIMoveToAction : public UBTBCharacterAction
{
	GENERATED_BODY()
	
public:

protected:
	virtual void Act(ABTBCharacter* Character) override;

private:


public:

protected:

private:
	UPROPERTY(EditDefaultsOnly, Category = "Focus")
	bool bEnableLookingAtTarget;
	
};
