// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameOneGameMode.h"

#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"

void ABTBMiniGameOneGameMode::BeginPlay()
{
	Super::BeginPlay();
	AssignGunToPlayer();
}

void ABTBMiniGameOneGameMode::AssignGunToPlayer()
{
	Gun = GetWorld()->SpawnActor<ABTBGun>(GunClass);
	if (Gun)
	{
		Gun->AttachToComponent(PlayerCharacterArray[0]->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
		PlayerCharacterArray[0]->SetGun(Gun);
	}
}
