// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once


#include "BackToBack/Characters/BTBCharacter.h"
#include "CoreMinimal.h"
#include "BTBDataAsset.h"
#include "BTBCharacterAction.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBCharacterAction : public UBTBDataAsset
{
	GENERATED_BODY()

public:
	void Act(ABTBCharacter* character);
	
};


