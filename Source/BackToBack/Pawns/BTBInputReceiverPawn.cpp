// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBInputReceiverPawn.h"
#include "BackToBack/GameStructs/BTBStructs.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "BackToBack/PlayerControllers/BTBPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InputActionValue.h"

void ABTBInputReceiverPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Send Data to player character


	//Reset Button states
	RightTrigger.ResetDownReleaseState();
	LeftTrigger.ResetDownReleaseState();
	RightButton.ResetDownReleaseState();
	LeftButton.ResetDownReleaseState();
	DownButton.ResetDownReleaseState();
	UpButton.ResetDownReleaseState();
}

void ABTBInputReceiverPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const ABTBPlayerController* PC = Cast<ABTBPlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = PC != nullptr ?
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()) : nullptr;
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(Subsystem))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMapping, 0);

		PEI->BindAction(RightTriggerInputAction, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::RightTriggerInputTriggered);
		PEI->BindAction(LeftTriggerInputAction, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::LeftTriggerInputTriggered);
		PEI->BindAction(RightButtonInputAction, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::RightButtonInputTriggered);
		PEI->BindAction(LeftButtonInputAction, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::LeftButtonInputTriggered);
		PEI->BindAction(UpButtonInputAction, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::UpButtonInputTriggered);
		PEI->BindAction(DownButtonInputAction, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::DownButtonInputTriggered);

		PEI->BindAction(AxisInputAction, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::SetAxisInput);
		PEI->BindAction(AxisInputAction, ETriggerEvent::Completed, this, &ABTBInputReceiverPawn::SetAxisInput);
	}
}

void ABTBInputReceiverPawn::RightTriggerInputTriggered(const FInputActionValue& Val)
{
	ButtonStateSetData(RightTrigger, Val.Get<bool>());
}

void ABTBInputReceiverPawn::LeftTriggerInputTriggered(const FInputActionValue& Val)
{
	ButtonStateSetData(LeftTrigger, Val.Get<bool>());
}

void ABTBInputReceiverPawn::RightButtonInputTriggered(const FInputActionValue& Val)
{
	ButtonStateSetData(RightButton, Val.Get<bool>());
}

void ABTBInputReceiverPawn::LeftButtonInputTriggered(const FInputActionValue& Val)
{
	ButtonStateSetData(LeftButton, Val.Get<bool>());
}

void ABTBInputReceiverPawn::DownButtonInputTriggered(const FInputActionValue& Val)
{
	ButtonStateSetData(DownButton, Val.Get<bool>());
}

void ABTBInputReceiverPawn::UpButtonInputTriggered(const FInputActionValue& Val)
{
	ButtonStateSetData(UpButton, Val.Get<bool>());
}

void ABTBInputReceiverPawn::SetAxisInput(const FInputActionValue& Val)
{
	AxisInput = Val.Get<FInputActionValue::Axis2D>();
}

void ABTBInputReceiverPawn::ButtonStateSetData(FButtonState& ButtonState, const bool Value)
{
	ButtonState.bIsHeld = Value;
	if (Value)
	{
		ButtonState.bIsDown = true;
	}
	else
	{
		ButtonState.bIsReleased = true;
	}
}