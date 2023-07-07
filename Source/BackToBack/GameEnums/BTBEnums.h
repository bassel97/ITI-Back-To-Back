// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBEnums.generated.h"

/**
 * This will hold all the enums that we need for our game
 */

UENUM(BlueprintType)
enum class RightTriggerButtonStates : uint8
{
	None,
	Shoot,
	Throw,
	Summon
};

UENUM(BlueprintType)
enum class LeftTriggerButtonStates : uint8
{
	None,
	Dash
};

UENUM(BlueprintType)
enum class RightButtonStates : uint8
{
	None,
	Pause
};

UENUM(BlueprintType)
enum class LeftButtonStates : uint8
{
	None,
	SwitchGun,
	MeleeAttack
};

UENUM(BlueprintType)
enum class UpButtonStates : uint8
{
	None,
	Jump
};

UENUM(BlueprintType)
enum class DownButtonStates : uint8
{
	None,
};

UENUM(BlueprintType)
enum class StartButtonStates : uint8
{
	None,
};