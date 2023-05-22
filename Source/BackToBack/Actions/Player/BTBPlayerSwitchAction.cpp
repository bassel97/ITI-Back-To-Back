// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerSwitchAction.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBTBPlayerSwitchAction::Act(ABTBCharacter* Character)
{
	const TObjectPtr<ABTBPlayableCharacter> PlayableCharacter = Cast<ABTBPlayableCharacter>(Character);
	const TObjectPtr<ABTBGun> MyGun = PlayableCharacter->GetGun();

	if (Character == nullptr)
	{
		return;
	} 
	
	if (Character->GetbStartSwitching())
	{
		MyGun->GunSkeletal->SetSimulatePhysics(false);
		MyGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		MyGun->AttachToComponent(PlayableCharacter->OtherPlayer->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");

	}
	
}
