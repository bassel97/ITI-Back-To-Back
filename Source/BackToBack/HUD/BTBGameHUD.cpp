// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGameHUD.h"

FVector2d UBTBGameHUD::GetScreenResolution()
{
	FVector2D Result;

	Result.X = GSystemResolution.ResX;
	Result.Y = GSystemResolution.ResY;

	return Result;
}

void UBTBGameHUD::SetOverlayResolution()
{
	
}

void UBTBGameHUD::NativeConstruct()
{
	Super::NativeConstruct();
}


