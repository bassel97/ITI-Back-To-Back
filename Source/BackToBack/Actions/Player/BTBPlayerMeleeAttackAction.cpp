// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerMeleeAttackAction.h"

#include "BackToBack/Actors/BTBSpear.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"

void UBTBPlayerMeleeAttackAction::Act(ABTBCharacter* Character)
{
	TObjectPtr<ABTBMiniGameTwoPlayableCharacter> MG2PlayableCharacter = Cast<ABTBMiniGameTwoPlayableCharacter>(Character);
	if (Character == nullptr)
	{
		return;
	}
	if (Character->LeftButtonState == ELeftButtonStates::MeleeAttack)
	{
		if (MG2PlayableCharacter->GetSpear() != nullptr)
		{
			if (MG2PlayableCharacter->GetSpear()->IsAttachedTo(MG2PlayableCharacter))
			{
					MG2PlayableCharacter->SetbIsAttacking(true);
			}
		}
	}
}
