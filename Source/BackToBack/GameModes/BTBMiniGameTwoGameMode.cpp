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
	
	Cast<ABTBMiniGameTwoPlayableCharacter>(PlayerCharacterArray[0])->PlayerDash.AddDynamic(this, &ABTBMiniGameTwoGameMode::ChangeDashBar);
	Cast<ABTBMiniGameTwoPlayableCharacter>(PlayerCharacterArray[1])->PlayerDash.AddDynamic(this, &ABTBMiniGameTwoGameMode::ChangeDashBar);

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
	}
}

void ABTBMiniGameTwoGameMode::SetTopDownCameraReferenceForEachPlayer()
{
	PlayerCharacterArray[0]->TopDownCameraPtr = SingleCameraPtr;
	PlayerCharacterArray[1]->TopDownCameraPtr = SingleCameraPtr;
}

void ABTBMiniGameTwoGameMode::ChangeDashBar(float value)
{
	GameWidget->SetDashPercent(value);
}
