// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGameHUD.h"
#include "Components/RetainerBox.h"
#include "Components/TextBlock.h"


void UBTBGameHUD::NativeConstruct()
{
	Super::NativeConstruct();
	Score->SetText(FText::AsNumber(0));
	DashPercent->SetPercent(1);
}

void UBTBGameHUD::SetScore(const int32 Value)
{
	if(Score)
	{
		Score->SetText(FText::AsNumber(Value));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Score is nullptr"));
	}
}

void UBTBGameHUD::SetDashPercent(float Value)
{
	if(DashPercent)
	{
		DashPercent->SetPercent(Value);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NULL Dash"));
	}
}
