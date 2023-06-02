// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBHumanoidCharacter.h"
#include "BTBAICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAIDeath);

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBAICharacter : public ABTBHumanoidCharacter
{
	GENERATED_BODY()

public:
	
protected:
	
private:

	

public:
	UPROPERTY()
	FOnAIDeath OnAIDeath;
	
protected:
	
private:
};
