// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPlayableCharacter.h"
#include "BTBMiniGameThreePlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBMiniGameThreePlayableCharacter : public ABTBPlayableCharacter
{
	GENERATED_BODY()

public:

protected:
	virtual void SetMoveValue(const float Value) override;
	virtual void SetRotationValue(const float Value) override;

private:


	
public:

protected:

private:
	
};
