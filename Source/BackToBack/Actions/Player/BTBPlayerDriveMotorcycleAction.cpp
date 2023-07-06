// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerDriveMotorcycleAction.h"

#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/Vehicles/BTBMotorcycle.h"

void UBTBPlayerDriveMotorcycleAction::Act(ABTBCharacter* Character)
{
	const TObjectPtr<ABTBPlayableCharacter> Player = Cast<ABTBPlayableCharacter>(Character);
	if(!ensure(Player != nullptr))
	{
		return;
	}
	const TObjectPtr<ABTBMotorcycle> Motorcycle = Cast<ABTBMotorcycle>(Player->Vehicle);
	if(!ensure(Motorcycle != nullptr))
	{
		return;
	}
	Motorcycle->Steer(Player->GetUserInput_Y());
	Motorcycle->Throttle(Player->GetUserInput_X());
	
}
