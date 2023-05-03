// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMainMenuGameMode.h"
#include "Blueprint/UserWidget.h"

void ABTBMainMenuGameMode::BeginPlay()
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
