// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerShootAction.h"
#include "BackToBack/Actors/BTBObjectPoolComponent.h"
#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameOnePlayableCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Components/SceneCaptureComponent2D.h"

void UBTBPlayerShootAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	
	if (Character->GetbStartShoot())
	{
		const auto PlayableCharacter = Cast<ABTBPlayableCharacter>(Character);
		const auto Camera2D = PlayableCharacter->GetComponentByClass(USceneCaptureComponent2D::StaticClass());
		const auto Camera2DSceneComp = Cast<USceneComponent>(Camera2D);
		const auto ShootingDirection = Camera2DSceneComp->GetComponentRotation().Vector();
		
		Gun = Cast<ABTBMiniGameOnePlayableCharacter>(Character)->GetGun();
		if (Gun != nullptr)
		{
			Gun->Shoot(ShootingDirection);
			Character->SetbStartShoot(false);
		}
	}
	
}



