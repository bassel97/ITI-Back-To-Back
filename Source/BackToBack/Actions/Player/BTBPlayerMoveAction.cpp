// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerMoveAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBTBPlayerMoveAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	
	if (Character->TopDownCameraPtr != nullptr)
	{
		const float MoveValue_X = Character->GetUserInput_X();
		const FVector CameraRight = Character->TopDownCameraPtr->GetActorRightVector();
	
		const float MoveValue_Y = Character->GetUserInput_Y();
		const FVector CameraForward = Character->TopDownCameraPtr->GetActorForwardVector();

		if (MoveValue_X != 0 || MoveValue_Y != 0)
		{
			Character->AddMovementInput(CameraRight, MoveValue_X);
			Character->AddMovementInput(CameraForward, MoveValue_Y);
		}
	}
}
