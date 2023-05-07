// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterJumpAction.h"

void UBTBCharacterJumpAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}

	if (Character->GetbStartJump())
	{
		Character->Jump();
		UE_LOG(LogTemp, Warning, TEXT("JUMP From Action"));

	}
	
}
