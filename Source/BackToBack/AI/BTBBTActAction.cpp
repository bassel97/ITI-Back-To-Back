// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBBTActAction.h"
#include "BackToBack/Actions/BTBCharacterAction.h"
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
	
	const ABTBAIController* MyController = Cast<ABTBAIController>(OwnerComp.GetOwner());
	APawn* MyPawn = MyController ? MyController->GetPawn() : nullptr;
	
	const auto Character = Cast<ABTBAICharacter>(MyPawn);
	Action->Act(Character);
	
	return EBTNodeResult::Succeeded;
}