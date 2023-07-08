// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBEnums.generated.h"

/**
 * This will hold all the enums that we need for our game
 */

UENUM(BlueprintType)
enum class ERightTriggerButtonStates : uint8
{
	None,
	Shoot,
	Throw,
	Summon
};

UENUM(BlueprintType)
enum class ELeftTriggerButtonStates : uint8
{
	None,
	Dash
};

UENUM(BlueprintType)
enum class ERightButtonStates : uint8
{
	None,
	Pause
};

UENUM(BlueprintType)
enum class ELeftButtonStates : uint8
{
	None,
	SwitchGun,
	MeleeAttack
};

UENUM(BlueprintType)
enum class EUpButtonStates : uint8
{
	None,
	Jump
};

UENUM(BlueprintType)
enum class EDownButtonStates : uint8
{
	None,
};

UENUM(BlueprintType)
enum class EStartButtonStates : uint8
{
	None,
};