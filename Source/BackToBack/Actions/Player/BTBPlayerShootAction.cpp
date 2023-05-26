// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerShootAction.h"
#include "BackToBack/Actors/BTBObjectPoolComponent.h"
#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameOnePlayableCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"

void UBTBPlayerShootAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	
	if (Character->GetbStartShoot())
	{
		Gun = Cast<ABTBMiniGameOnePlayableCharacter>(Character)->GetGun();
		if (Gun != nullptr)
		{
			Gun->Shoot();
			Character->SetbStartShoot(false);
		}
	}
	
}



