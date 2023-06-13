// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacter.h"

#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BackToBack/Actors/BTBCamera.h"


ABTBCharacter::ABTBCharacter()
{
	UserInput_X = 0;
	UserInput_Y = 0;
}

void ABTBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickDeltaTime = DeltaTime;
	
	for (const auto& Action : CharacterActions)
	{
		Action->Act(this);
	}
}

void ABTBCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetbStartPool(true);
	SetbIsPaused(false);
}

