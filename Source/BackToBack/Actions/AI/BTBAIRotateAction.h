// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBAIRotateAction.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBAIRotateAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:

protected:
	virtual void Act(ABTBCharacter* Character) override;

private:


public:

protected:

private:
};