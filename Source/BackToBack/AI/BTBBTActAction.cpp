// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBBTActAction.h"
#include "BackToBack/Actions/BTBCharacterAction.h"


UBTBBTActAction::UBTBBTActAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), Action(nullptr)
{
	NodeName = "ActAction";
}

EBTNodeResult::Type UBTBBTActAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	const AController* MyController = Cast<AController>(OwnerComp.GetOwner());
	APawn* MyPawn = MyController ? MyController->GetPawn() : nullptr;
	
	const auto Character = Cast<ABTBCharacter>(MyPawn);
	Action->Act(Character);
	
	return Result;
}