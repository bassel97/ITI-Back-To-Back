// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPlayableCharacter.h"
#include "BTBMiniGameTwoPlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBMiniGameTwoPlayableCharacter : public ABTBPlayableCharacter
{
	GENERATED_BODY()

public:

protected:
	virtual float GetUserInput_X() override;
	virtual float GetUserInput_Y() override;

private:


	
public:

protected:

private:

};
