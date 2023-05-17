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
		if (Character->GetbStartSwitching() )
		{
			

			if (!PlayableCharacter->bGunAttached)
			{
				if (myGun->GetbIsOverlapping())
				{
					myGun->GunMesh->SetSimulatePhysics(false);

					myGun->AttachToComponent(PlayableCharacter->GetMesh()->GetAttachmentRoot(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");

					PlayableCharacter->bGunAttached = true;

				}

			}
			

		}
	}

	if (bIsAI)
	{
		////
	}
}
