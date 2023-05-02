// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterRotateAction.h"

UBTBCharacterRotateAction::UBTBCharacterRotateAction()
{
	/*PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 0.f;*/
}

void UBTBCharacterRotateAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	
	FRotator NewRotation = FRotator(Rotation.X, Rotation.Y, Rotation.Z);

	FQuat QuatRotation = FQuat(NewRotation);

	Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);



}


