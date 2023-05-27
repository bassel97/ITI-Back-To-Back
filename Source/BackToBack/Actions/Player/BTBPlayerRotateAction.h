// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBPlayerRotateAction.generated.h"

class ABTBCharacter;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBPlayerRotateAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:

protected:

	virtual void Act(ABTBCharacter* Character) override;

	UPROPERTY(EditDefaultsOnly)
	FVector RelativeCenterOfRotation;
	
private:

	
	
public:

protected:

private:

};
