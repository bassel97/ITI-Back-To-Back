// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBCharacterAction.h"
#include "BTBCharacterJumpAction.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBCharacterJumpAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:
	virtual void Act(ABTBCharacter* Character) override;

};
