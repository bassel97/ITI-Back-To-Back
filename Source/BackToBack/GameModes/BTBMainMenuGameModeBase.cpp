// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMainMenuGameModeBase.h"
#include "Blueprint/UserWidget.h"

void ABTBMainMenuGameModeBase::BeginPlay()
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
