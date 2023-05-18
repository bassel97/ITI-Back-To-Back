// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

//#include "BackToBack/Characters/BTBCharacter.h"
#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBPlayerMoveAction.generated.h"

class ABTBCharacter;
class ABTBAICharacter;


/**
 * Our Move
 */
UCLASS()
class BACKTOBACK_API UBTBPlayerMoveAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:
	//virtual void Act(ABTBCharacter* Character, bool bIsAI = false) override;
	virtual void Act(ABTBCharacter* Character) override;

};
