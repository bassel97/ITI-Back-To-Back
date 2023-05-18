// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterSwitchAction.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTBCharacterSwitchAction::Act(ABTBCharacter* Character, const bool bIsAI)
{

	ABTBPlayableCharacter* PlayableCharacter = Cast<ABTBPlayableCharacter>(Character);

	ABTBGun* myGun = PlayableCharacter->GetGun();

	if (Character == nullptr)
	{
		return;
	} 

	if (!bIsAI)
	{ 
		if (Character->GetbStartSwitching())
		{
			if (!PlayableCharacter->bGunAttached)
			{
				UE_LOG(LogTemp, Warning, TEXT("firsh switch cond!!"));

				if (myGun->GetbIsOverlapping())
				{
					UE_LOG(LogTemp, Warning, TEXT("Switching!!"));

					myGun->GunMesh->SetSimulatePhysics(false);

					myGun->AttachToComponent(PlayableCharacter->GetMesh()->GetAttachmentRoot(), FAttachmentTransformRules::SnapToTargetIncludingScale, "GunSocket");

					PlayableCharacter->bGunAttached = true;
				}
			}

			if (PlayableCharacter->bGunAttached)
			{
				UE_LOG(LogTemp, Warning, TEXT("ditch it!!"));
				myGun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
				myGun->SetActorLocationAndRotation(PlayableCharacter->GetMesh()->GetSocketLocation("GunSocket"), PlayableCharacter->GetMesh()->GetSocketRotation("GunSocket"));
				PlayableCharacter->bGunAttached = false;
				//myGun->GunMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				//myGun->GunMesh->SetSimulatePhysics(true);

			}
			

		}
	}

	if (bIsAI)
	{
		////
	}
}
