// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacter.h"

#include "BackToBack/Actions/BTBCharacterAction.h"


void ABTBCharacter::Tick(float DeltaTime)
{
	
	for (const auto& Action : CharacterActions)
	{
		Action->Act(this);
	}
}

bool ABTBCharacter::GetbStartJump()
{
	return bStartJump;
}

void ABTBCharacter::SetbStartJump(bool value)
{
	bStartJump = value;
}

