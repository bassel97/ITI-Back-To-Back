// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once


#include "BackToBack/Characters/BTBCharacter.h"
#include "CoreMinimal.h"
#include "BackToBack/DataAssets/BTBDataAsset.h"
#include "BTBCharacterAction.generated.h"

/**
 * 
 */
UCLASS(abstract)
class BACKTOBACK_API UBTBCharacterAction : public UBTBDataAsset
{
	GENERATED_BODY()


public:
	virtual void Act(ABTBCharacter* Character) PURE_VIRTUAL(UBTBCharacterAction::Act);
	
};


