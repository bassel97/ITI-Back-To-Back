// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPawn.h"
#include "BackToBack/GameStructs/BTBStructs.h"
#include "BTBInputReceiverPawn.generated.h"

struct FInputActionValue;
class FGameStructs;
class UInputAction;
class ABTBPlayableCharacter;
class UInputMappingContext;

/**
 * Our InputReceiverPawn
 */
UCLASS()
class BACKTOBACK_API ABTBInputReceiverPawn final : public ABTBPawn
{
	GENERATED_BODY()

public:

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void RightTriggerInputTriggered(const FInputActionValue& Val);
	void LeftTriggerInputTriggered(const FInputActionValue& Val);
	void RightButtonInputTriggered(const FInputActionValue& Val);
	void LeftButtonInputTriggered(const FInputActionValue& Val);
	void DownButtonInputTriggered(const FInputActionValue& Val);
	void UpButtonInputTriggered(const FInputActionValue& Val);
	void StartButtonInputTriggered(const FInputActionValue& Val); //New
	void SetAxisInput(const FInputActionValue& Val);

	void HandleDownButton() const;
	void HandleUpButton() const;
	void HandleLeftButton() const;
	void HandleRightButton() const;
	void HandleRightTrigger();
	void HandleLeftTrigger() const;
	void HandleAxisInputAction() const;
	void HandleStartButton() const; //New
	
private:
	static void ButtonStateSetData(FButtonState& ButtonState, const bool Value);
	
public:
	TObjectPtr<ABTBPlayableCharacter> PlayerCharacterPtr;
	
	UPROPERTY(VisibleAnywhere, Category = "Class Variables")
	int32 PlayerIndex;
	
	/** Input Actions start*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> RightTriggerInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> LeftTriggerInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> RightButtonInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> LeftButtonInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> DownButtonInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> UpButtonInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> AxisInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> StartButtonInputAction; //New
	/** Input Actions end*/
	
	
protected:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputMappingContext> InputMapping;
	
private:
	/** Buttons States start*/
	UPROPERTY(VisibleAnywhere, Category = "Buttons States")
	FButtonState RightTrigger = {};

	UPROPERTY(VisibleAnywhere, Category = "Buttons States")
	FButtonState LeftTrigger = {};

	UPROPERTY(VisibleAnywhere, Category = "Buttons States")
	FButtonState RightButton = {};
	
	UPROPERTY(VisibleAnywhere, Category = "Buttons States")
	FButtonState LeftButton = {};

	UPROPERTY(VisibleAnywhere, Category = "Buttons States")
	FButtonState DownButton = {};

	UPROPERTY(VisibleAnywhere, Category = "Buttons States")
	FButtonState UpButton = {};
	
	UPROPERTY(VisibleAnywhere, meta = (ClampMin = -1, ClampMax = 1), Category = "Buttons")
	FVector2D AxisInput;

	UPROPERTY(VisibleAnywhere, Category = "Buttons States")
	FButtonState StartButton = {}; //New
	/** Buttons States end*/

	FTimerHandle TimerHandle;
	FTimerHandle LeftButtonTimerHandle;


};
