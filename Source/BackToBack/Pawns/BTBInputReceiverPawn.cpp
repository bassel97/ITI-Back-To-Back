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
	
}

void ABTBInputReceiverPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	const ABTBPlayerController* PC = Cast<ABTBPlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions

	if (PC && IsValid(Subsystem))
	{
		// Clear out existing mapping, and add our mapping
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMapping, 0);
		PEI->BindAction(InputMove, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::PrintXYZ);
		PEI->BindAction(InputMove, ETriggerEvent::Triggered, this, &ABTBInputReceiverPawn::PrintXYZ);
	}
}

void ABTBInputReceiverPawn::PrintXYZ(const FInputActionValue& Val)
{
	FVector2D Input = Val.Get<FInputActionValue::Axis2D>();
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s"), *Input.ToString()));
}
