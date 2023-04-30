// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.generated.h"

/**
 * This will hold all the structs that we need for our game
 */

#pragma region GLOBAL GAME STRUCTS


USTRUCT(BlueprintType)
struct FButtonState
{
 GENERATED_BODY()

 UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
 bool bIsDown;

 UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
 bool bIsHeld;

 UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
 bool bIsReleased;
};


#pragma endregion GLOBAL GAME STRUCTS
