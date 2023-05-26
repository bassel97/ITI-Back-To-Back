// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerSwitchAction.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameOnePlayableCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBTBPlayerSwitchAction::Act(ABTBCharacter* Character)
{
	const TObjectPtr<ABTBMiniGameOnePlayableCharacter> PlayableCharacter = Cast<ABTBMiniGameOnePlayableCharacter>(Character);
	const TObjectPtr<ABTBMiniGameOnePlayableCharacter> OtherCharacter = Cast<ABTBMiniGameOnePlayableCharacter>(PlayableCharacter->OtherPlayer);
	const TObjectPtr<ABTBGun> Gun = PlayableCharacter->GetGun();

	if (PlayableCharacter == nullptr)
	{
		return;
	} 
	
	if (PlayableCharacter->GetbStartSwitching() && PlayableCharacter->IsOverlapping && Gun != nullptr )
	{
		OtherCharacter->SetGun(Gun);
		Gun->AttachToComponent(OtherCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "GunSocket");
		//PlayableCharacter->SetGun(nullptr);
	}
	
}



#pragma region BackUp switch
//PlayableCharacter->PlayAnimMontage(PlayableCharacter->SwitchMontage);
//MyGun->GunSkeletal->SetSimulatePhysics(false);
//MyGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
//PlayableCharacter->SetbStartSwitching(false);
////PlayableCharacter->IsOverlapping = false;

#pragma endregion
