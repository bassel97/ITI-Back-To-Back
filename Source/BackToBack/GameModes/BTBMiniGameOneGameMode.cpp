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

	ABTBMiniGameOnePlayableCharacter* MGOnePlayer = Cast<ABTBMiniGameOnePlayableCharacter>(PlayerCharacterArray[0]);

	Gun = GetWorld()->SpawnActor<ABTBGun>(GunClass);
	if (Gun)
	{
		Gun->AttachToComponent(MGOnePlayer->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
		MGOnePlayer->SetGun(Gun);
	}
}
