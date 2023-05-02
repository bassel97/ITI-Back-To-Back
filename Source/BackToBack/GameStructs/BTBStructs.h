// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBStructs.generated.h"

/**
 * This will hold all the structs that we need for our game
 */

#pragma region GLOBAL GAME STRUCTS


USTRUCT(BlueprintType)
struct FButtonState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bIsDown;

	UPROPERTY(BlueprintReadOnly)
	bool bIsHeld;

	UPROPERTY(BlueprintReadOnly)
	bool bIsReleased;

	void ResetDownReleaseState()
	{
		bIsDown = false;
		bIsReleased = false;
	}

	// Constructor
	FButtonState()
	{
		bIsDown = false;
		bIsHeld = false;
		bIsReleased = false;
	}

};


#pragma endregion GLOBAL GAME STRUCTS
