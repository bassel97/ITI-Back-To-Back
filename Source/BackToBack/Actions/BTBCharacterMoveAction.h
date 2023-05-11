// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

//#include "BackToBack/Characters/BTBCharacter.h"
#include "CoreMinimal.h"
#include "BTBCharacterAction.h"
#include "BTBCharacterMoveAction.generated.h"

class ABTBCharacter;
class ABTBAICharacter;


/**
 * Our Move
 */
UCLASS()
class BACKTOBACK_API UBTBCharacterMoveAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:
	virtual void Act(ABTBCharacter* Character) override;

};
