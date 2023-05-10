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

void ABTBCharacter::SetbStartJump(bool Value)
{
	bStartJump = Value;
}

bool ABTBCharacter::GetbStartRotate()
{
	return bStartRotate;
}

void ABTBCharacter::SetbStartRotate(bool Value)
{
	bStartRotate = Value;
}

bool ABTBCharacter::GetbStartMove()
{
	return bStartMove;
}

void ABTBCharacter::SetbStartMove(bool Value)
{
	bStartMove = Value;
}

float ABTBCharacter::GetRotationValue()
{
	return RotationValue;
}

void ABTBCharacter::SetRotationValue(float Value)
{
	RotationValue = Value;

}

float ABTBCharacter::GetMoveValue()
{
	return MoveValue;
}

void ABTBCharacter::SetMoveValue(float Value)
{
	MoveValue = Value;
}



