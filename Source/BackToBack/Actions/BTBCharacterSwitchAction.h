// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBCharacterAction.h"
#include "BTBCharacterSwitchAction.generated.h"


class ABTBCharacter;
class ABTBAICharacter;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBCharacterSwitchAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:
	virtual void Act(ABTBCharacter* Character, bool bIsAI = false) override;
	
};
