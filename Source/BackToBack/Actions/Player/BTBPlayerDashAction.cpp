// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerDashAction.h"

#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"


void UBTBPlayerDashAction::Act(ABTBCharacter* Character)
{

	ABTBMiniGameTwoPlayableCharacter* MG2Player = Cast<ABTBMiniGameTwoPlayableCharacter>(Character);
	if (Character == nullptr)
	{
		return;
	}

	if (Character->GetbStartDashing() )
	{
		
			MG2Player->Dash();
			//UE_LOG(LogTemp,Warning,TEXT("dashing Is: %f"), MG2Player->DashMeter);
	}

	if (Character->GetbStartDashing() == false)
	{
		MG2Player->SetbIsDashing(false);
	}
	
}
