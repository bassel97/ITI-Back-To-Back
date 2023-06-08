// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBPlayerMeleeAttackAction.generated.h"

/**
 **/
UCLASS()
class BACKTOBACK_API UBTBPlayerMeleeAttackAction : public UBTBCharacterAction
{
	GENERATED_BODY()

protected:
	virtual void Act(ABTBCharacter* Character) override;
};
