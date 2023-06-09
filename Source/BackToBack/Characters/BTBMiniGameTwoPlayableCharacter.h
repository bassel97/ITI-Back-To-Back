// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPlayableCharacter.h"
#include "BTBMiniGameTwoPlayableCharacter.generated.h"

class ABTBSpear;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBMiniGameTwoPlayableCharacter : public ABTBPlayableCharacter
{
	GENERATED_BODY()

public:
	ABTBMiniGameTwoPlayableCharacter();

	void SetSpear(ABTBSpear* Spear);
	ABTBSpear* GetSpear();

protected:
	virtual float GetUserInput_X() override;
	virtual float GetUserInput_Y() override;

private:


	
public:
	TObjectPtr<ABTBSpear> SpearActor;

protected:


private:

};
