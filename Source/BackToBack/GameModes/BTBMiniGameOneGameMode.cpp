// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameOneGameMode.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBMiniGameOnePlayableCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"

void ABTBMiniGameOneGameMode::BeginPlay()
{
	Super::BeginPlay();
	AssignGunToPlayer();
}

void ABTBMiniGameOneGameMode::AssignGunToPlayer()
{
	const TObjectPtr<ABTBMiniGameOnePlayableCharacter> MG1_Player = Cast<ABTBMiniGameOnePlayableCharacter>(PlayerCharacterArray[0]);

	Gun = GetWorld()->SpawnActor<ABTBGun>(GunClass);
	if (Gun)
	{
		Gun->AttachToComponent(MG1_Player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
		MG1_Player->SetGun(Gun);
		MG1_Player->bGunAttached = true;
	}
}
