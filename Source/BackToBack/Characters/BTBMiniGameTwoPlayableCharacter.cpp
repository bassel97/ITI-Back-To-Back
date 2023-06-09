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


// This is DUMB but its fixing an error IDK why this is happening
// If you remove it, character will spin around its Z axis forever after the first move
float ABTBMiniGameTwoPlayableCharacter::GetUserInput_X()
{
	if(UserInput_X > 0.01)	return UserInput_X;
	if(UserInput_X < -0.01)	return UserInput_X;
	return 0;
}

float ABTBMiniGameTwoPlayableCharacter::GetUserInput_Y()
{
	if(UserInput_Y > 0.01)	return UserInput_Y;
	if(UserInput_Y < -0.01)	return UserInput_Y;
	return 0;
}

