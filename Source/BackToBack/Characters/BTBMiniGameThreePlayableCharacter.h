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
	virtual void SetUserInput_Y(const float Value) override;
	virtual void SetUserInput_X(const float Value) override;
	
	
};
