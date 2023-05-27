// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerJumpAction.h"

#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"

void UBTBPlayerJumpAction::Act(ABTBCharacter* Character)
{
	if (Character->GetbStartJump())
	{
		Character->Jump();
	}
}
