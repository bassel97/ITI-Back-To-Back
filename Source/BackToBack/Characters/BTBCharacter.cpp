// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacter.h"

#include "BackToBack/Actions/Character/BTBCharacterAction.h"


void ABTBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (const auto& Action : CharacterActions)
	{
		Action->Act(this);
	}
}

void ABTBCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetbStartPool(true);
}

