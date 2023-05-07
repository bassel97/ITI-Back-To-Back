// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterRotateAction.h"


void UBTBCharacterRotateAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}

	if (Character->GetbStartRotate())
	{
		FRotator CharRotation = Character->GetActorRotation();

		FRotator NewRotation = CharRotation.Add(0, 1, 0);
		
		FQuat QuatRotation = FQuat(NewRotation);

		Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

		
	}





}


