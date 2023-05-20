// Copyright di-tri studio, Inc. All Rights Reserved.


#include "MiniGameOnePlayableCharacter.h"

float AMiniGameOnePlayableCharacter::GetRotationValue()
{
	if(RotationValue >= 0.925f && OtherPlayer->RotationValue >= 0.925f)		return 1;
	if(RotationValue <= -0.975f && OtherPlayer->RotationValue <= -0.975f)		return -1;
	return 0;
}
