// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBInputReceiverPawn.h"

#include "BackToBack/GameModes/BTBGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ABTBInputReceiverPawn::ABTBInputReceiverPawn()
{
	BaseTurnAtRate = 45.0f;
	BaseLookUpAtRate = 45.0f;
}

void ABTBInputReceiverPawn::Start()
{
	if(const UWorld* World = GetWorld())
	{
		if(ABTBGameModeBase* GameMode = Cast<ABTBGameModeBase>(UGameplayStatics::GetGameMode(World)))
		{
			GameMode->SpawnPlayer(PlayerIndex, this);
			UE_LOG(LogTemp, Display, TEXT("HELLO"));
		}
	}
	
}

void ABTBInputReceiverPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ABTBInputReceiverPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABTBInputReceiverPawn::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABTBInputReceiverPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABTBInputReceiverPawn::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ABTBInputReceiverPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABTBInputReceiverPawn::MoveForward(const float Value)
{
	if(IsValid(Controller) && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABTBInputReceiverPawn::MoveRight(const float Value)
{
	if(IsValid(Controller) && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABTBInputReceiverPawn::TurnAtRate(const float Value)
{
	AddControllerYawInput(Value * BaseTurnAtRate * GetWorld()->GetDeltaSeconds());
}

void ABTBInputReceiverPawn::LookUpAtRate(const float Value)
{
	AddControllerYawInput(Value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}