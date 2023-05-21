// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerSwitchAction.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
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
		if (!PlayableCharacter->bGunAttached)
		{
			if (MyGun->GetbIsOverlapping())
			{
				MyGun->AttachToComponent(PlayableCharacter->GetMesh()->GetAttachmentRoot(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");
				PlayableCharacter->bGunAttached = true;
			}
		}
	}
	
}
