// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerMoveAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBTBPlayerMoveAction::Act(ABTBCharacter* Character)
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
	
	const float RotationAngle = MoveValue_X * (540.0f / PI);
	const FRotator TargetRotation = FRotator(0,RotationAngle * Character->TickDeltaTime,0);
	Character->AddActorLocalRotation(TargetRotation);

#if UE_EDITOR
	// UE_LOG(LogTemp, Warning, TEXT("Move X = %f"), MoveValue_X);
	// UE_LOG(LogTemp, Warning, TEXT("Move Y = %f"), MoveValue_Y);
	// UE_LOG(LogTemp, Warning, TEXT("InputAngle = %f"), RotationAngle);
#endif
	
}
