// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoGameMode.h"
#include "BackToBack/Actors/BTBSpear.h"

#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/HUD/BTBGameHUD.h"

void ABTBMiniGameTwoGameMode::BeginPlay()
{
	Super::BeginPlay();
	AssignSpearToPlayer();
	GameWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ABTBMiniGameTwoGameMode::AssignSpearToPlayer()
{
	if (!ensure(SpearClass != nullptr))
	{
		return;
	}

	const TObjectPtr<ABTBMiniGameTwoPlayableCharacter> MG2_Player = Cast<ABTBMiniGameTwoPlayableCharacter>(PlayerCharacterArray[0]);
	Spear = GetWorld()->SpawnActor<ABTBSpear>(SpearClass);
	if (Spear)
	{
		Spear->AttachToComponent(MG2_Player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandSocket"));
		MG2_Player->SetSpear(Spear);
		
	}
}
