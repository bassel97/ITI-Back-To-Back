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
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/GameModes/BTBGameplayGameMode.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"


void ABTBInputReceiverPawn::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Send Data to player character
	HandleDownButton();
	HandleUpButton();
	HandleLeftButton();
	HandleRightButton();
	HandleRightTrigger();
	HandleLeftTrigger();
	HandleAxisInputAction();
	HandleStartButton(); //New
	
	//Reset Button states
	RightTrigger.ResetDownReleaseState();
	LeftTrigger.ResetDownReleaseState();
	RightButton.ResetDownReleaseState();
	LeftButton.ResetDownReleaseState();
	DownButton.ResetDownReleaseState();
	UpButton.ResetDownReleaseState();
	StartButton.ResetDownReleaseState();//New
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

void ABTBInputReceiverPawn::StartButtonInputTriggered(const FInputActionValue& Val) //NEW
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
		PlayerCharacter->SetbStartJump(false);
	}

	if (UpButton.bIsHeld)
	{
		PlayerCharacter->SetbStartJump(true);
	}

}

void ABTBInputReceiverPawn::HandleLeftButton() const
{
	if (LeftButton.bIsDown)
	{
		PlayerCharacter->SetbStartSwitching(true);
		//PlayerCharacter->PlayAnimMontage();
		PlayerCharacter->SetbStartAttack(true);
	}

	if (LeftButton.bIsReleased)
	{
		PlayerCharacter->SetbStartSwitching(false);
		//PlayerCharacter->SetbStartAttack(false);
	}

	if (LeftButton.bIsHeld)
	{
		//PlayerCharacter->SetbStartSwitching(true);
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
		PlayerCharacter->SetbStartShoot(true);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABTBInputReceiverPawn::HandleRightTrigger, 2.0f, false);
		PlayerCharacter->SetbStartThrowing(true);
		PlayerCharacter->SetbStartSummoning(true);
	}
	
	if (RightTrigger.bIsReleased)
	{
		PlayerCharacter->SetbStartShoot(false);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		PlayerCharacter->SetbStartThrowing(false);
		PlayerCharacter->SetbStartSummoning(false);

	}

	
	/*if (RightTrigger.bIsHeld)
	{
		PlayerCharacter->SetbStartThrowing(false);
		PlayerCharacter->SetbStartSummoning(true);
	}*/
}

void ABTBInputReceiverPawn::HandleLeftTrigger() const
{
	if (LeftTrigger.bIsDown)
	{

	}

	if (LeftTrigger.bIsReleased)
	{
	}

	if (LeftTrigger.bIsHeld)
	{

	}
}

void ABTBInputReceiverPawn::HandleAxisInputAction() const
{
	PlayerCharacter->SetUserInput_X(AxisInput.X);
	PlayerCharacter->SetUserInput_Y(AxisInput.Y);
}

void ABTBInputReceiverPawn::HandleStartButton() const //New
{
	if (RightButton.bIsDown)
	{
		UE_LOG(LogTemp, Warning, TEXT("Start Pressed"));
		PlayerCharacter->SetbIsPaused(true);
		
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
