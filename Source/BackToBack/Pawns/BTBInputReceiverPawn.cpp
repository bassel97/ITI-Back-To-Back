// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBInputReceiverPawn.h"
#include "BackToBack/GameStructs/BTBStructs.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "BackToBack/PlayerControllers/BTBPlayerController.h"
#include "EnhancedInputComponent.h"
#include  "BackToBack\AnimationInstance\MilesAnimInstance.h"
#include "InputAction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InputActionValue.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BackToBack/Actions/Player/BTBPlayerSwitchAction.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/GameModes/BTBGameplayGameMode.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"


void ABTBInputReceiverPawn::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(PlayerCharacterPtr->bIsDead)	return;
	
	// Send Data to player character
	HandleDownButton();
	HandleUpButton();
	HandleLeftButton();
	HandleRightButton();
	HandleRightTrigger();
	HandleLeftTrigger();
	HandleAxisInputAction();
	HandleStartButton();
	
	//Reset Button states
	RightTrigger.ResetDownReleaseState();
	LeftTrigger.ResetDownReleaseState();
	RightButton.ResetDownReleaseState();
	LeftButton.ResetDownReleaseState();
	DownButton.ResetDownReleaseState();
	UpButton.ResetDownReleaseState();
	StartButton.ResetDownReleaseState();
	AxisInput.Zero();
}

void ABTBInputReceiverPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const TObjectPtr<ABTBPlayerController> PC = Cast<ABTBPlayerController>(GetController());
	
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem =
		PC != nullptr ? ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()) : nullptr;

	const TObjectPtr<UEnhancedInputComponent> PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
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
		PEI->BindAction(StartButtonInputAction, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::StartButtonInputTriggered);//New

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

void ABTBInputReceiverPawn::StartButtonInputTriggered(const FInputActionValue& Val)
{
	ButtonStateSetData(StartButton, Val.Get<bool>());
}

void ABTBInputReceiverPawn::SetAxisInput(const FInputActionValue& Val)
{
	AxisInput = Val.Get<FInputActionValue::Axis2D>();
}



void ABTBInputReceiverPawn::HandleDownButton() const
{
	if (DownButton.bIsDown)
	{
	}

	if (DownButton.bIsReleased)
	{
	}

	if (DownButton.bIsHeld)
	{
	}
}

void ABTBInputReceiverPawn::HandleUpButton() const
{
	if (UpButton.bIsDown)
	{
	}

	if (UpButton.bIsReleased)
	{
		PlayerCharacterPtr->SetbStartJump(false);
	}

	if (UpButton.bIsHeld)
	{
		PlayerCharacterPtr->SetbStartJump(true);
	}

}

void ABTBInputReceiverPawn::HandleLeftButton() const
{
	if (LeftButton.bIsDown)
	{
		PlayerCharacterPtr->SetbStartSwitching(true);
		PlayerCharacterPtr->SetbStartAttack(true);
	}

	if (LeftButton.bIsReleased)
	{
		PlayerCharacterPtr->SetbStartSwitching(false);
		PlayerCharacterPtr->SetbStartAttack(false);
	}

	if (LeftButton.bIsHeld)
	{
		
	}
}

void ABTBInputReceiverPawn::HandleRightButton() const
{
	if (RightButton.bIsDown)
	{
	}

	if (RightButton.bIsReleased)
	{
	}

	if (RightButton.bIsHeld)
	{
	}
}

void ABTBInputReceiverPawn::HandleRightTrigger()
{
	if (RightTrigger.bIsDown)
	{
		PlayerCharacterPtr->SetbStartShoot(true);
		PlayerCharacterPtr->SetbStartThrowing(true);
		PlayerCharacterPtr->SetbStartSummoning(true);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABTBInputReceiverPawn::HandleRightTrigger, 2.0f, false);
	}
	
	if (RightTrigger.bIsReleased)
	{
		PlayerCharacterPtr->SetbStartShoot(false);
		PlayerCharacterPtr->SetbStartThrowing(false);
		PlayerCharacterPtr->SetbStartSummoning(false);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}

	
	if (RightTrigger.bIsHeld)
	{
		if (!RightTrigger.bIsDown)
		{
			PlayerCharacterPtr->SetbStartThrowing(false);
		}
	}
}

void ABTBInputReceiverPawn::HandleLeftTrigger() const
{
	if (LeftTrigger.bIsDown)
	{
		PlayerCharacterPtr->SetbStartDashing(true);
		UE_LOG(LogTemp,Warning,TEXT("Dashing"));
	}

	if (LeftTrigger.bIsReleased)
	{
		//PlayerCharacterPtr->SetbStartDashing(false);
		Cast<ABTBMiniGameTwoPlayableCharacter>(PlayerCharacterPtr)->SetbIsDashing(false);

	}

	if (LeftTrigger.bIsHeld)
	{
		if (!LeftTrigger.bIsDown)
		{
			PlayerCharacterPtr->SetbStartDashing(false);
		}
	}
}

void ABTBInputReceiverPawn::HandleAxisInputAction() const
{
	PlayerCharacterPtr->SetUserInput_X(AxisInput.X);
	PlayerCharacterPtr->SetUserInput_Y(AxisInput.Y);
}

void ABTBInputReceiverPawn::HandleStartButton() const
{
	if (RightButton.bIsDown)
	{
		PlayerCharacterPtr->SetbIsPaused(true);
	}

	if (RightButton.bIsReleased)
	{

	}
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
