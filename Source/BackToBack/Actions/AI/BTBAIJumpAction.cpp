// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBAIJumpAction.h"

#include "BackToBack/Characters/BTBCharacter.h"

void UBTBAIJumpAction::Act(ABTBCharacter* Character)
{
	Character->Jump();
}
