// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPawn.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/GameStructs/BTBStructs.h"
#include "BTBInputReceiverPawn.generated.h"

class FGameStructs;
class UInputAction;
struct FInputActionValue;
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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void PrintXYZ(const FInputActionValue& Val);
	
private:
	
	
public:
	UPROPERTY(VisibleAnywhere, Category="Class Variables")
	int32 PlayerIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputMove;
	
protected:

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputMappingContext> InputMapping;

	
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
