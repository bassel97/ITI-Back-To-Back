// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBAILookAtAction.generated.h"

/**
 * Our version of Looking At that AI uses to rotate,
 * similar to PlayerRotateAction but using AI.
 */
UCLASS()
class BACKTOBACK_API UBTBAILookAtAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:

protected:
	virtual void Act(ABTBCharacter* Character) override;
	
	
};
