// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTBMainHUD.generated.h"

/**
 * Our version of the HUD MainMenu 
 */
UCLASS()
class BACKTOBACK_API UBTBMainHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Start_BTN;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Quit_BTN;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnStartClick();

	UFUNCTION()
		void OnQuitClick();
};
