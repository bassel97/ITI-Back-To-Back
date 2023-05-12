// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterMoveAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTBCharacterMoveAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	
	if(auto PlayablerCharacter = Cast<ABTBPlayableCharacter>(Character))
	{
		float MoveValue = Character->GetMoveValue();
		if(Character->GetbStartMove())
		{
		
			UE_LOG(LogTemp, Warning, TEXT("Move btn clicked, %f"), MoveValue);
			if (MoveValue != 0.f)
			{
				FVector Forward = Character->GetActorForwardVector();
				const FTransform Transform = FTransform(Forward);
				//Character->AddActorLocalTransform(Transform, false, 0, ETeleportType::None);
				Character->AddMovementInput(Forward, MoveValue);
			}
		}
	}

	if(const auto BTBAICharacter = Cast<ABTBAICharacter>(Character))
	{
		if(const auto BTBAIController = Cast<ABTBAIController>(BTBAICharacter->GetController()))
		{
			const auto PlayerObject =
				BTBAIController->GetBlackboardComponent()->GetValueAsObject("PlayerActor");

			const auto PlayerActor = Cast<AActor>(PlayerObject);
			if(PlayerActor)
			{
				BTBAIController->MoveToActor(PlayerActor);
				BTBAIController->SetFocus(PlayerActor);
			}
		}
	}

	
}
