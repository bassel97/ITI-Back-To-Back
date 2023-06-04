// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoGameMode.h"

#include "BackToBack/HUD/BTBGameHUD.h"

void ABTBMiniGameTwoGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameWidget->SetVisibility(ESlateVisibility::Hidden);
}
