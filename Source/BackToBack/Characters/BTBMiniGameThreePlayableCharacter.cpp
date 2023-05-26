// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameThreePlayableCharacter.h"

#include "BackToBack/Vehicles/BTBMotorcycle.h"
#include "Kismet/GameplayStatics.h"

void ABTBMiniGameThreePlayableCharacter::SetMoveValue(const float Value)
{
	TObjectPtr<ABTBMotorcycle> Motorcycle = Cast<ABTBMotorcycle>(Vehicle);
	if(Motorcycle != nullptr)
	{
		// Throttle
		Motorcycle->CurrentSpeed =
			FMath::FInterpTo(
				Motorcycle->CurrentSpeed,
				Value * Motorcycle->MaxSpeed,
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				4);
	}
	
}

void ABTBMiniGameThreePlayableCharacter::SetRotationValue(const float Value)
{
	TObjectPtr<ABTBMotorcycle> Motorcycle = Cast<ABTBMotorcycle>(Vehicle);
	if(Motorcycle != nullptr)
	{
		// Steer
		Motorcycle->CurrentSteeringAngle =
			FMath::FInterpTo(
				Motorcycle->CurrentSteeringAngle,
				Value * Motorcycle->MaxSteeringAngle,
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				4
				);
	}
	
}
