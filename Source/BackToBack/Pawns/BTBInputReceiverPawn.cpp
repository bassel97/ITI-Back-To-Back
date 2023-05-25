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
	
	//Reset Button states
	RightTrigger.ResetDownReleaseState();
	LeftTrigger.ResetDownReleaseState();
	RightButton.ResetDownReleaseState();
	LeftButton.ResetDownReleaseState();
	DownButton.ResetDownReleaseState();
	UpButton.ResetDownReleaseState();
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
		//PlayerCharacter->PlayAnimMontage(PlayerCharacter->SwitchMontage);

		//for (auto Element : PlayerCharacter->CharacterActions)
		//{
		//	if (Element.)
		//	{
		//		
		//	}
		//}
		

	}

	if (LeftButton.bIsReleased)
	{
		
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
		PlayerCharacter->SetbStartShoot(true);
		UE_LOG(LogTemp, Warning, TEXT("Left click pressed"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABTBInputReceiverPawn::HandleRightTrigger, 2.0f, false);
	}
	
	if (RightTrigger.bIsReleased)
	{
		PlayerCharacter->SetbStartShoot(false);
		UE_LOG(LogTemp, Warning, TEXT("Left click Released"));
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	/*if (RightTrigger.bIsHeld)
	{
		PlayerCharacter->SetbStartShoot(true);
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
	//Rotating
	PlayerCharacter->SetRotationValue(AxisInput.X);
	//UE_LOG(LogTemp, Warning, TEXT("Rotation btn clicked, %f"), AxisInput.X);
	
	
	//Moving
	PlayerCharacter->SetMoveValue(AxisInput.Y);
	//UE_LOG(LogTemp, Warning, TEXT("Move btn clicked, %f"), AxisInput.Y);
}
//	}
//	else
//	{
//		PlayerCharacter->SetbStartRotate(false);
//	}
//	
//}
//void ABTBInputReceiverPawn::HandleMoveAction()
//{
//	if (AxisInput.Y != 0)
//	{
//		float input = FMath::Clamp(AxisInput.Y, -1.f, 1.f);
//		//float input = AxisInput.Y;
//
//		//float rotSpeed = 30;
//		PlayerCharacter->SetbStartMove(true);
//		PlayerCharacter->SetMoveValue(input);
//		//UE_LOG(LogTemp, Warning, TEXT("Move btn clicked, %f"), input);
//	}
//	else
//	{
//		PlayerCharacter->SetbStartMove(false);
//	}
//}  
#pragma endregion


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
