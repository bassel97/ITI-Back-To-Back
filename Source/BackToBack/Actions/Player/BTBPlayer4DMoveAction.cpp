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
	
	UE_LOG(LogTemp, Warning, TEXT("Move X = %f"), MoveValue_X);
	UE_LOG(LogTemp, Warning, TEXT("Move Y = %f"), MoveValue_Y);
	UE_LOG(LogTemp, Warning, TEXT("Forward = %s"), *Forward.ToString());

	// if(Character->GetController() != nullptr && (MoveValue_X != 0 || MoveValue_Y != 0))
	// {
	// 	const FVector Direction_X = FRotationMatrix(Character->GetController()->GetControlRotation()).GetUnitAxis(EAxis::X);
	// 	Character->AddMovementInput(Direction_X, MoveValue_X);
	//
	// 	const FVector Direction_Y = FRotationMatrix(Character->GetController()->GetControlRotation()).GetUnitAxis(EAxis::Y);
	// 	Character->AddMovementInput(Direction_Y, MoveValue_Y);
	// }
}
