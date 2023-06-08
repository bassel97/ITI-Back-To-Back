// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/Actors/BTBSpear.h"

ABTBMiniGameTwoPlayableCharacter::ABTBMiniGameTwoPlayableCharacter()
{
}

void ABTBMiniGameTwoPlayableCharacter::SetSpear(ABTBSpear* Spear)
{
	SpearActor = Spear;
}

ABTBSpear* ABTBMiniGameTwoPlayableCharacter::GetSpear()
{
	return SpearActor;
}

void ABTBMiniGameTwoPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}
