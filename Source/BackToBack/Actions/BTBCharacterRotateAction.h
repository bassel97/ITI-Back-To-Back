// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBCharacterAction.h"
#include "BTBCharacterRotateAction.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBCharacterRotateAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:
	UBTBCharacterRotateAction();
	
public:
	UPROPERTY(EditAnywhere, Category = "Movement")
		FVector Rotation;

public:
	virtual void Act(ABTBCharacter* Character) override;
};
