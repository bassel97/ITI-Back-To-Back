// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterRotateAction.h"

#include "GameFramework/PawnMovementComponent.h"


void UBTBCharacterRotateAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}

	if (Character->GetbStartRotate())
	{

		FRotator NewRotation = FRotator(0, Character->GetRotationValue(), 0);

		FQuat QuatRotation = FQuat(NewRotation);

		Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

		UE_LOG(LogTemp, Warning, TEXT("Yaw angle is : %f"), Character->GetActorRotation().Yaw);
		
	}





}


