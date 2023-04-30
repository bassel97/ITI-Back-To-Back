// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPawn.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/GameStructs/GameStructs.h"
#include "BTBInputReceiverPawn.generated.h"

class FGameStructs;
/**
 * Our InputReceiverPawn
 */
UCLASS()
class BACKTOBACK_API ABTBInputReceiverPawn final : public ABTBPawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	
	[[nodiscard]] ABTBPlayableCharacter* Get_PlayerCharacter() const
	{
		return PlayerCharacter;
	}

	void Set_PlayerCharacter(ABTBPlayableCharacter* Player_Character)
	{
		this->PlayerCharacter = Player_Character;
	}

protected:

private:
	
	
public:
	UPROPERTY(VisibleAnywhere, Category="Class Variables")
	int32 PlayerIndex;
	
protected:
	
private:
	TObjectPtr<ABTBPlayableCharacter> PlayerCharacter;

	UPROPERTY(VisibleAnywhere, Category = "Buttons")
	FButtonState RightTrigger = {};

	UPROPERTY(VisibleAnywhere, Category = "Buttons")
	FButtonState LeftTrigger = {};

	UPROPERTY(VisibleAnywhere, Category = "Buttons")
	FButtonState RightButton = {};
	
	UPROPERTY(VisibleAnywhere, Category = "Buttons")
	FButtonState LeftButton = {};

	UPROPERTY(VisibleAnywhere, Category = "Buttons")
	FButtonState DownButton = {};

	UPROPERTY(VisibleAnywhere, Category = "Buttons")
	FButtonState UpButton = {};
	
	UPROPERTY(VisibleAnywhere, meta = (ClampMin = -1, ClampMax = 1), Category = "Buttons")
	FVector2D AxisInput;
};
