// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerSummonAction.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/Actors/BTBSpear.h"

void UBTBPlayerSummonAction::Act(ABTBCharacter* Character)
{
    if (Character == nullptr) 
    {
        return;
    }

    if (Character->GetbStartSummoning())
    {
        ABTBMiniGameTwoPlayableCharacter* Player = Cast<ABTBMiniGameTwoPlayableCharacter>(Character);
        
        if (Player->GetSpear() != nullptr && Player != nullptr)
        {
            if (!Player->GetSpear()->IsAttachedTo(Player))
            {
                if (Player->OtherPlayer != nullptr)
                {
                    ABTBMiniGameTwoPlayableCharacter* OtherOther = Cast<ABTBMiniGameTwoPlayableCharacter>(Player->OtherPlayer);
                    if(OtherOther->GetSpear()->IsAttachedTo(OtherOther))
                    {
                        OtherOther->GetSpear()->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, true));
                    }
                }
                Player->Summon();
            }
        }
    }
}