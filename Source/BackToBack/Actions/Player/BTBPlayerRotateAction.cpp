// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerRotateAction.h"
#include "BackToBack/Characters/BTBCharacter.h"


void UBTBPlayerRotateAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	

    const FTransform CharacterTransform = Character->GetTransform();
    const FVector RelativeCenterOfRotationWS = CharacterTransform.TransformVector(RelativeCenterOfRotation);
    const FTransform LocalRotateCenter = FTransform(CharacterTransform.GetRotation(), RelativeCenterOfRotationWS);
    Character->SetActorTransform(LocalRotateCenter.Inverse() * Character->GetTransform());
	
    const float RotationValue = Character->GetUserInput_X();
	const FRotator CurrentRotation = Character->GetActorRotation();
	const FRotator TargetRotation = FRotator(0, RotationValue, 0);
	const FQuat SmoothedQuatRotation = FQuat::Slerp(CurrentRotation.Quaternion(), TargetRotation.Quaternion(), 0.95);
    Character->AddActorLocalRotation(SmoothedQuatRotation);

	Character->SetActorTransform(LocalRotateCenter * Character->GetTransform());

}


