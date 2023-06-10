// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBAnimNotifyStateThrow.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/Actors/BTBSpear.h"

void UBTBAnimNotifyStateThrow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		Miles = Cast<ABTBMiniGameTwoPlayableCharacter>(MeshComp->GetOwner());
		if (Miles)
		{
			Miles->GetSpear()->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, true));

			Miles->GetSpear()->Throw(Miles->GetActorForwardVector(), 2000.f);
			Miles->bSpearAttached = Miles->GetSpear()->IsAttachedTo(Miles);

			if (!Miles->bSpearAttached)
			{
				Miles->bIsThrowing = false;
			}

		}
	}
}

void UBTBAnimNotifyStateThrow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}
