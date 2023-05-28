// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGameHUD.h"
#include "Components/RetainerBox.h"
#include "BackToBack/Characters/BTBEnemyCharacter.h"
#include "Components/TextBlock.h"


void UBTBGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	Score->SetText(FText::AsNumber(0));
}

void UBTBGameHUD::SetScore(int32 ScoreValue)
{
	Score->SetText(FText::AsNumber(ScoreValue));
}


