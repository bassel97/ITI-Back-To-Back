// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBBTActAction.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ActAction::UBTTask_ActAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), Action(nullptr)
{
	NodeName = "ActAction";
}

EBTNodeResult::Type UBTTask_ActAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	const TObjectPtr<AAIController> OwnerAIController = OwnerComp.GetAIOwner();
	if(!ensure(OwnerAIController != nullptr))
	{
		return EBTNodeResult::Failed;
	}
	
	const TObjectPtr<APawn> OwnerPawn = OwnerAIController->GetPawn();
	const TObjectPtr<ABTBCharacter> BTBCharacter = Cast<ABTBCharacter>(OwnerPawn);
	if(BTBCharacter->Health > 0)
	{
		Action->Act(BTBCharacter);
	}
	//Action->Act(BTBCharacter);
	
	return EBTNodeResult::Succeeded;
}