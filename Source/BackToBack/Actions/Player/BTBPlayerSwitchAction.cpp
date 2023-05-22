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
		myGun->GunSkeletal->SetSimulatePhysics(false);
		myGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		myGun->SetActorLocationAndRotation(PlayableCharacter->GetMesh()->GetSocketLocation("GunSocket"), PlayableCharacter->GetMesh()->GetSocketRotation("GunSocket"));
		myGun->AttachToComponent(PlayableCharacter->OtherPlayer->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");

		//myGun

		//if (!PlayableCharacter->bGunAttached)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("firsh switch cond!!"));

		//	if (myGun->GetbIsOverlapping())
		//	{
		//		UE_LOG(LogTemp, Warning, TEXT("Switching!!"));

		//		myGun->GunSkeletal->SetSimulatePhysics(false);

		//		myGun->AttachToComponent(PlayableCharacter->GetMesh()->GetAttachmentRoot(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");

		//		PlayableCharacter->bGunAttached = true;
		//	}
		//}

		//if (PlayableCharacter->bGunAttached)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("ditch it!!"));
		//	myGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		//	myGun->SetActorLocationAndRotation(PlayableCharacter->GetMesh()->GetSocketLocation("GunSocket"), PlayableCharacter->GetMesh()->GetSocketRotation("GunSocket"));
		//	PlayableCharacter->bGunAttached = false;
		//	//myGun->GunMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//	//myGun->GunMesh->SetSimulatePhysics(true);
		//}


	}
	
}
