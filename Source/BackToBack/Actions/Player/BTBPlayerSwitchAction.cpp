// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerSwitchAction.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBTBPlayerSwitchAction::Act(ABTBCharacter* Character)
{
	TObjectPtr<ABTBPlayableCharacter> PlayableCharacter = Cast<ABTBPlayableCharacter>(Character);
	TObjectPtr<ABTBGun> MyGun = PlayableCharacter->GetGun();

	if (PlayableCharacter == nullptr)
	{
		return;
	} 
	
	if (Character->GetbStartSwitching() )
	{
		if (!PlayableCharacter->GetMesh()->IsPlaying())
		{
			UE_LOG(LogTemp, Warning, TEXT("Is playing"));
			PlayableCharacter->PlayAnimMontage(PlayableCharacter->SwitchMontage);
		}
		
		//PlayableCharacter->PlayAnimMontage(PlayableCharacter->SwitchMontage);
		//MyGun->GunSkeletal->SetSimulatePhysics(false);
		//MyGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		//PlayableCharacter->SetbStartSwitching(false);
		////PlayableCharacter->IsOverlapping = false;
		PlayableCharacter->OtherPlayer->SetGun(MyGun);
		UE_LOG(LogTemp, Warning, TEXT("The gun is %s"), *MyGun.GetName());
		MyGun->AttachToComponent(PlayableCharacter->OtherPlayer->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");
		PlayableCharacter->SetGun(nullptr);

	}
	
}
