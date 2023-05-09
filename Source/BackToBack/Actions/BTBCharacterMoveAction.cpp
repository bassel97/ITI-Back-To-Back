// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterMoveAction.h"

void UBTBCharacterMoveAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	float moveValue = Character->GetMoveValue();
	if(Character->GetbStartMove())
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Move btn clicked, %f"), moveValue);
		if (moveValue != 0.f)
		{
			FVector Forward = FVector(Character->GetMoveValue(), 0.f, 0.f);
			FTransform Transform = FTransform(Forward);
			//Character->AddMovementInput(Forward, moveValue);
			Character->AddActorLocalTransform(Transform, false, 0, ETeleportType::None);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Move btn not clicked, %f"), moveValue);
	}
	
}
