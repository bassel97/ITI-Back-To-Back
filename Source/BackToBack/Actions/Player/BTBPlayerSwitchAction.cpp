// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerSwitchAction.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameOnePlayableCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBTBPlayerSwitchAction::Act(ABTBCharacter* Character)
{
	TObjectPtr<ABTBMiniGameOnePlayableCharacter> PlayableCharacter = Cast<ABTBMiniGameOnePlayableCharacter>(Character);
	TObjectPtr<ABTBMiniGameOnePlayableCharacter> otherCharacter = Cast<ABTBMiniGameOnePlayableCharacter>(PlayableCharacter->OtherPlayer);
	TObjectPtr<ABTBGun> MyGun = PlayableCharacter->GetGun();

	if (PlayableCharacter == nullptr)
	{
		return;
	} 
	
	if (PlayableCharacter->IsOverlapping && MyGun != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("The gun is %s"), *MyGun.GetName());
		//MyGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		MyGun->AttachToComponent(PlayableCharacter->OtherPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "GunSocket");
		otherCharacter->SetGun(MyGun);
		PlayableCharacter->SetGun(nullptr);
	}
	
}



#pragma region BackUp switch
//PlayableCharacter->PlayAnimMontage(PlayableCharacter->SwitchMontage);
//MyGun->GunSkeletal->SetSimulatePhysics(false);
//MyGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
//PlayableCharacter->SetbStartSwitching(false);
////PlayableCharacter->IsOverlapping = false;

#pragma endregion
