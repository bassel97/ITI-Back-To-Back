// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoGameMode.h"
#include "BackToBack/Actors/BTBSpear.h"

#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/HUD/BTBGameHUD.h"

void ABTBMiniGameTwoGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	AssignSpearToPlayer();
	SetTopDownCameraReferenceForEachPlayer();
	
	GameWidget->SetVisibility(ESlateVisibility::Hidden);

}

void ABTBMiniGameTwoGameMode::AssignSpearToPlayer()
{
	if (!ensure(SpearClass != nullptr))
	{
		return;
	}

	const TObjectPtr<ABTBMiniGameTwoPlayableCharacter> MG2_Player = Cast<ABTBMiniGameTwoPlayableCharacter>(PlayerCharacterArray[0]);
	SpearPtr = GetWorld()->SpawnActor<ABTBSpear>(SpearClass);
	if (SpearPtr)
	{
		SpearPtr->AttachToComponent(MG2_Player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandSocket"));
		MG2_Player->SetSpear(SpearPtr);
	}
}

void ABTBMiniGameTwoGameMode::SetTopDownCameraReferenceForEachPlayer()
{
	PlayerCharacterArray[0]->TopDownCameraPtr = SingleCameraPtr;
	PlayerCharacterArray[1]->TopDownCameraPtr = SingleCameraPtr;
}