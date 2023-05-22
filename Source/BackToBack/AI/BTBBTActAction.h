// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTBBTActAction.generated.h"

class UBTBCharacterAction;

/**
 * Our Behaviour Tree Task Node
 */
UCLASS()
class BACKTOBACK_API UBTTask_ActAction : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

public:
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:

	
	
public:

protected:
	
private:
	UPROPERTY(EditAnywhere, Category = "Actions")
	TObjectPtr<UBTBCharacterAction> Action;
	
};

