// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacter.h"

#include "BackToBack/Actions/BTBCharacterAction.h"


void ABTBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

bool ABTBCharacter::GetbStartRotate()
{
	return bStartRotate;
}

void ABTBCharacter::SetbStartRotate(bool value)
{
	bStartRotate = value;
}

