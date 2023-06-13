// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoGameMode.h"
#include "BackToBack/Actors/BTBSpear.h"

#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/HUD/BTBGameHUD.h"

void ABTBMiniGameTwoGameMode::BeginPlay()
{
	Super::BeginPlay();
	AssignSpearToPlayer();
	//GameWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ABTBMiniGameTwoGameMode::AssignSpearToPlayer()
{
	if (!ensure(SpearClass != nullptr))
	{
		return;
	}

	const TObjectPtr<ABTBMiniGameTwoPlayableCharacter> MG2_PlayerOne = Cast<ABTBMiniGameTwoPlayableCharacter>(PlayerCharacterArray[0]);
	const TObjectPtr<ABTBMiniGameTwoPlayableCharacter> MG2_PlayerTwo = Cast<ABTBMiniGameTwoPlayableCharacter>(PlayerCharacterArray[1]);
	SpearPtr = GetWorld()->SpawnActor<ABTBSpear>(SpearClass);
	
	if (SpearPtr)
	{
		SpearPtr->AttachToComponent(MG2_PlayerOne->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandSocket"));
		MG2_PlayerOne->SetSpear(SpearPtr);
		MG2_PlayerTwo->SetSpear(SpearPtr);
		//MG2_Player->bSpearAttached = true;
	}
}
