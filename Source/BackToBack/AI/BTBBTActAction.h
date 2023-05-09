// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTBBTActAction.generated.h"

class UBTBCharacterAction;

/**
 * Our Behaviour Tree Task Node
 */
UCLASS()
class BACKTOBACK_API UBTBBTActAction : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = "Actions")
	TObjectPtr<UBTBCharacterAction> Action;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
