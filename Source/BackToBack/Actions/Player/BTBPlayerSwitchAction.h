// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBPlayerSwitchAction.generated.h"


class ABTBCharacter;
class ABTBAICharacter;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBPlayerSwitchAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:



protected:

	virtual void Act(ABTBCharacter* Character) override;

	//UPROPERTY(EditDefaultsOnly)
	//FVector RelativeCenterOfRotation;

private:

public:

protected:

private:
	
};
