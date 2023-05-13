// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterJumpAction.h"

#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"

void UBTBCharacterJumpAction::Act(ABTBCharacter* Character, const bool bIsAI)
{
	if (Character == nullptr)
	{
		return;
	}
	
	if(!bIsAI)
	{
		if(TObjectPtr<ABTBPlayableCharacter> PlayableCharacter = Cast<ABTBPlayableCharacter>(Character))
		{
			if (Character->GetbStartJump())
			{
				Character->Jump();
				//UE_LOG(LogTemp, Warning, TEXT("We are jumping, we are sinking"));

			}
		}
	}

	
	if(bIsAI)
	{
		if(const TObjectPtr<ABTBAICharacter> BTBAICharacter = Cast<ABTBAICharacter>(Character))
		{
			BTBAICharacter->Jump();
		}
	}

	
}
