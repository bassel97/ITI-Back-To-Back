// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerDashAction.h"

#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"


void UBTBPlayerDashAction::Act(ABTBCharacter* Character)
{

	ABTBMiniGameTwoPlayableCharacter* MG2Player = Cast<ABTBMiniGameTwoPlayableCharacter>(Character);
	if (Character == nullptr)
	{
		return;
	}

	if (Character->LeftTriggerButtonState == ELeftTriggerButtonStates::Dash)
	{
			MG2Player->Dash();
	}

	if (Character->LeftTriggerButtonState == ELeftTriggerButtonStates::None)
	{
		MG2Player->SetbIsDashing(false);
	}
	
}
