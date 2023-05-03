// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMainHUD.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>

#pragma region MainMenu
void UBTBMainHUD::NativeConstruct()
{
	if (Start_BTN)
	{
		Start_BTN->OnClicked.AddDynamic(this, &UBTBMainHUD::OnStartClick);
	}
	if (Quit_BTN)
	{
		Quit_BTN->OnClicked.AddDynamic(this, &UBTBMainHUD::OnQuitClick);
	}
}

void UBTBMainHUD::OnStartClick()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		UGameplayStatics::OpenLevel(World, TEXT("TestPreCommit"));
	}
}

void UBTBMainHUD::OnQuitClick()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("Quit"));
	}
}
#pragma endregion
