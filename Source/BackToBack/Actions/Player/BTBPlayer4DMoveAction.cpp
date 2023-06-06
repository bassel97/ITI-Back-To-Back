// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayer4DMoveAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBTBPlayer4DMoveAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	
	const float MoveValue_X = Character->GetUserInput_X();
	const FVector Right = Character->GetActorRightVector();
	
	const float MoveValue_Y = Character->GetUserInput_Y();
	const FVector Forward = Character->GetActorForwardVector();
	
	Character->AddMovementInput(Right, MoveValue_X);
	Character->AddMovementInput(Forward, MoveValue_Y);
	
}
