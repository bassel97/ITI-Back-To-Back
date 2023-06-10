#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBPlayerThrowAction.generated.h"

UCLASS()
class BACKTOBACK_API UBTBPlayerThrowAction : public UBTBCharacterAction
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
