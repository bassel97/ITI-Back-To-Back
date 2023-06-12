#include "BTBPlayerThrowAction.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/Actors/BTBSpear.h"

void UBTBPlayerThrowAction::Act(ABTBCharacter* Character)
{
    if (Character == nullptr)
    {
        return;
    }

    if (Character->GetbStartThrowing())
    {
        ABTBMiniGameTwoPlayableCharacter* Player = Cast<ABTBMiniGameTwoPlayableCharacter>(Character);
        if (Player->GetSpear()->IsAttachedTo(Player))
        {
            Player->Throw();
        }
    }
}
