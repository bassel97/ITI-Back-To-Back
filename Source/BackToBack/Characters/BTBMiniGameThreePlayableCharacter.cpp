// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameThreePlayableCharacter.h"

#include "BackToBack/Vehicles/BTBMotorcycle.h"
#include "Kismet/GameplayStatics.h"

void ABTBMiniGameThreePlayableCharacter::SetUserInput_Y(const float Value)
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!ensure(World != nullptr))
	{
		return;
	}
	
	const TObjectPtr<ABTBMotorcycle> Motorcycle = Cast<ABTBMotorcycle>(Vehicle);
	if(Motorcycle != nullptr)
	{
		// Throttle
		Motorcycle->CurrentSpeed =
			FMath::FInterpTo(
				Motorcycle->CurrentSpeed,
				Value * Motorcycle->MaxSpeed,
				UGameplayStatics::GetWorldDeltaSeconds(World),
				4);
	}
	
}

void ABTBMiniGameThreePlayableCharacter::SetUserInput_X(const float Value)
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!ensure(World != nullptr))
	{
		return;
	}
	
	const TObjectPtr<ABTBMotorcycle> Motorcycle = Cast<ABTBMotorcycle>(Vehicle);
	if(Motorcycle != nullptr)
	{
		// Steer
		Motorcycle->CurrentSteeringAngle =
			FMath::FInterpTo(
				Motorcycle->CurrentSteeringAngle,
				Value * Motorcycle->MaxSteeringAngle,
				UGameplayStatics::GetWorldDeltaSeconds(World),
				4);
	}
	
}
