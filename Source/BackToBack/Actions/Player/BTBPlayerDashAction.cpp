// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerDashAction.h"

#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBTBPlayerDashAction::Act(ABTBCharacter* Character)
{

	ABTBMiniGameTwoPlayableCharacter* MG2Player = Cast<ABTBMiniGameTwoPlayableCharacter>(Character);
	if (Character == nullptr)
	{
		return;
	}

	if (Character->GetbStartDashing())
	{
		UE_LOG(LogTemp,Warning,TEXT("Honga bonga"))
		Character->LaunchCharacter(Character->GetActorForwardVector()*300,false,false);
		MG2Player->SetbIsDashing(true);
		MG2Player->DashMeter -= 1;
	}
	
	// if (!Character->GetbStartDashing())
	// {
	// 	Character->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	// 	Character->GetCharacterMovement()->MaxAcceleration = 2400.f;
	// 	Character->GetCharacterMovement()->BrakingFriction = 0;
	// }
}
