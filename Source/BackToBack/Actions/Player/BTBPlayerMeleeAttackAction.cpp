// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerMeleeAttackAction.h"

#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"

void UBTBPlayerMeleeAttackAction::Act(ABTBCharacter* Character)
{
	TObjectPtr<ABTBMiniGameTwoPlayableCharacter> MG2PlayableCharacter = Cast<ABTBMiniGameTwoPlayableCharacter>(Character);

	if (Character == nullptr)
	{
		return;
	}

	if (Character->GetbStartAttack())
	{
		UE_LOG(LogTemp, Warning, TEXT("ATTACK"));
		MG2PlayableCharacter->Attack();
		//Character->PlayAnimMontage(attackMontage,1,NAME_None);
		//Character->SetbStartAttack(false);
	}
	//Character->PlayAnimMontage();
}
