// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterSwitchAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTBCharacterSwitchAction::Act(ABTBCharacter* Character, const bool bIsAI)
{
	if (Character == nullptr)
	{
		return;
	} 

	if (!bIsAI)
	{ 
		if (Character->GetbStartSwitching() )
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));
			UE_LOG(LogTemp, Warning, TEXT("Switching 2")); 
		}
	}

	if (bIsAI)
	{
		////
	}
}
