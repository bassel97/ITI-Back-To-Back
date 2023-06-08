// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGameOverHUD.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"

void UBTBGameOverHUD::NativeConstruct()
{
	Super::NativeConstruct();
	if(RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UBTBGameOverHUD::OnRestartButtonClick);
	}
}

void UBTBGameOverHUD::OnRestartButtonClick()
{
	
	UWorld* World = GetWorld();
	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}
