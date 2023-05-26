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
	
	if (PlayableCharacter->GetbStartSwitching() && PlayableCharacter->IsOverlapping && MyGun != nullptr )
	{
		otherCharacter->SetGun(MyGun);
		UE_LOG(LogTemp, Warning, TEXT("The gun is %s"), *MyGun.GetName());
		MyGun->AttachToComponent(otherCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "GunSocket");
		PlayableCharacter->SetGun(nullptr);

		//PlayableCharacter->IsOverlapping = false;
		//otherCharacter->IsOverlapping = false;
	}
	
}



#pragma region BackUp switch
//PlayableCharacter->PlayAnimMontage(PlayableCharacter->SwitchMontage);
//MyGun->GunSkeletal->SetSimulatePhysics(false);
//MyGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
//PlayableCharacter->SetbStartSwitching(false);
////PlayableCharacter->IsOverlapping = false;

#pragma endregion
