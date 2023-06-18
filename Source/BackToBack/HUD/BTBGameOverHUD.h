// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTBGameOverHUD.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBGameOverHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MainMenuButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnRestartButtonClick();

	UFUNCTION()
	void OnMainMenuButtonClick();
	
};
