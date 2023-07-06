// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMinigame2UI.h"
#include "Components/RetainerBox.h"
#include "Components/TextBlock.h"

void UBTBMinigame2UI::SetScore(int32 Value)
{
	if(Score)
	{
		Score->SetText(FText::AsNumber(Value));
	}
}

void UBTBMinigame2UI::NativeConstruct()
{
	Super::NativeConstruct();
	Score->SetText(FText::AsNumber(0));
}
