// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGameOverHUD.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"


void UBTBGameOverHUD::SetScore(UTextBlock* Value)
{
	if(Score)
	{
		Score->SetText(Value->GetText());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Score is nullptr"));
	}
}

void UBTBGameOverHUD::NativeConstruct()
{
	Super::NativeConstruct();
	if(RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UBTBGameOverHUD::OnRestartButtonClick);
	}

	if(MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UBTBGameOverHUD::OnMainMenuButtonClick);
	}
	
}


void UBTBGameOverHUD::OnRestartButtonClick()
{
	
	UWorld* World = GetWorld();
	if(World)
	{
		//UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
		//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

void UBTBGameOverHUD::OnMainMenuButtonClick()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMenu"));
	}
}
