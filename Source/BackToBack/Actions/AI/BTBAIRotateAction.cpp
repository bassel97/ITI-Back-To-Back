// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBAIRotateAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTBAIRotateAction::Act(ABTBCharacter* Character)
{
	if(const TObjectPtr<ABTBAIController> BTBAIController = Cast<ABTBAIController>(Character->GetController()))
	{
		const TObjectPtr<UObject> PlayerObject =
			BTBAIController->GetBlackboardComponent()->GetValueAsObject("PlayerActor");

		const TObjectPtr<AActor> PlayerActor = Cast<AActor>(PlayerObject);
		if(PlayerActor)
		{
			BTBAIController->SetFocus(PlayerActor);
		}
	}
}
