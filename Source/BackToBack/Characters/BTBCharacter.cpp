// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacter.h"

#include "BackToBack/DataAssets/BTBCharacterAction.h"

void ABTBCharacter::Tick(float DeltaTime)
{
	
	for (auto& Action : CharacterActions)
	{
		Action->Act(this);
	}
}
