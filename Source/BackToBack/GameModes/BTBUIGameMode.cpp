// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBUIGameMode.h"
#include "Blueprint/UserWidget.h"

void ABTBUIGameMode::BeginPlay()
{
	if (IsValid(BTBMainMenuWidgetClass))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), BTBMainMenuWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}
