// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPauseMenuHUD.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBTBPauseMenuHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeBTN)
	{
		ResumeBTN->OnPressed.AddUniqueDynamic(this, &UBTBPauseMenuHUD::OnResumeBtnClick);
	}

	if (QuitBTN)
	{
		QuitBTN->OnClicked.AddDynamic(this, &UBTBPauseMenuHUD::OnQuitBtnClick);
	}

	if (MainMenuBTN)
	{
		MainMenuBTN->OnClicked.AddDynamic(this, &UBTBPauseMenuHUD::OnMainMenuBtnClick);
	}
}

void UBTBPauseMenuHUD::OnResumeBtnClick()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Resume"));
		UGameplayStatics::SetGamePaused(World,false);
		RemoveFromParent();
	}
}

void UBTBPauseMenuHUD::OnQuitBtnClick()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (World)
	{
		FGenericPlatformMisc::RequestExit(false);

	}
}

void UBTBPauseMenuHUD::OnMainMenuBtnClick()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMenu2"));
	}

}
