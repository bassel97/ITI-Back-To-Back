// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerSwitchAction.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameOnePlayableCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"

void UBTBPlayerSwitchAction::Act(ABTBCharacter* Character)
{
	const TObjectPtr<ABTBMiniGameOnePlayableCharacter> PlayableCharacter = Cast<ABTBMiniGameOnePlayableCharacter>(Character);
	const TObjectPtr<ABTBMiniGameOnePlayableCharacter> OtherCharacter = Cast<ABTBMiniGameOnePlayableCharacter>(PlayableCharacter->OtherPlayer);
	const TObjectPtr<ABTBGun> Gun = PlayableCharacter->GetGun();

	if (PlayableCharacter == nullptr)
	{
		return;
	} 
	
	if (PlayableCharacter->LeftButtonState == LeftButtonStates::SwitchGun && PlayableCharacter->IsOverlapping && Gun != nullptr )
	{
		OtherCharacter->SetGun(Gun);
		Gun->AttachToComponent(OtherCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "GunSocket");
		PlayableCharacter->SetGun(nullptr);
		OtherCharacter->bGunAttached = true;
		PlayableCharacter->bGunAttached = false;
	}
	
}