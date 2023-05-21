// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBAIMoveToAction.h"

#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/AIControllers/BTBAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void UBTBAIMoveToAction::Act(ABTBCharacter* Character)
{
	if(const TObjectPtr<ABTBAIController> BTBAIController = Cast<ABTBAIController>(Character->GetController()))
	{
		const TObjectPtr<UObject> PlayerObject =
			BTBAIController->GetBlackboardComponent()->GetValueAsObject("PlayerActor");
	
		const TObjectPtr<AActor> PlayerActor = Cast<AActor>(PlayerObject);
		if(PlayerActor)
		{
			BTBAIController->MoveToActor(PlayerActor);
			
			if(bEnableLookingAtTarget)
			{
				BTBAIController->SetFocus(PlayerActor);
			}
		}
	}
}
