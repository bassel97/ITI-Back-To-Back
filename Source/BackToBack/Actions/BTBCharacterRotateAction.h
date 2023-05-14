// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBCharacterAction.h"
#include "BTBCharacterRotateAction.generated.h"

class ABTBCharacter;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBCharacterRotateAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:

protected:
	virtual void Act(ABTBCharacter* Character, bool bIsAI = false) override;
	float Angle;

	UPROPERTY(EditDefaultsOnly)
		float XCenterOfRotation;
private:

public:

protected:

private:

};
