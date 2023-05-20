// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerMoveAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTBPlayerMoveAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	
	const float MoveValue = Character->GetMoveValue();
	const FVector Forward = Character->GetActorForwardVector();
	
	const FTransform Transform = FTransform(Forward);
	Character->AddMovementInput(Forward, MoveValue);
	
	//UE_LOG(LogTemp, Warning, TEXT("Move btn clicked, %f"), MoveValue);

	
}
