// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterMoveAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTBCharacterMoveAction::Act(ABTBCharacter* Character, const bool bIsAI)
{
	if (Character == nullptr)
	{
		return;
	}

	if(!bIsAI)
	{
		const float MoveValue = Character->GetMoveValue();
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
	

	if(bIsAI)
	{

		if(const TObjectPtr<ABTBAIController> BTBAIController = Cast<ABTBAIController>(Character->GetController()))
		{
			const TObjectPtr<UObject> PlayerObject =
				BTBAIController->GetBlackboardComponent()->GetValueAsObject("PlayerActor");

			const TObjectPtr<AActor> PlayerActor = Cast<AActor>(PlayerObject);
			if(PlayerActor)
			{
				BTBAIController->MoveToActor(PlayerActor);
				BTBAIController->SetFocus(PlayerActor);
			}
		}
	}
	
	
}
