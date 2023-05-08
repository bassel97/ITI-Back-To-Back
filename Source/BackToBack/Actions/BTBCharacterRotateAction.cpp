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
		UE_LOG(LogTemp, Warning, TEXT("We are rotating, we are sinking"));
		//FRotator CharRotation = Character->GetActorRotation();

		//FRotator NewRotation = CharRotation.Add(0, Character->GetRotationValue() , 0);

		FRotator NewRotation = FRotator(0, Character->GetRotationValue(), 0);

		FQuat QuatRotation = FQuat(NewRotation);

		Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

		
	}





}


