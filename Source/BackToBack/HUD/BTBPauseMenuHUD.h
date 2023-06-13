// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTBPauseMenuHUD.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBPauseMenuHUD : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ResumeBTN;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> QuitBTN;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> MainMenuBTN;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnResumeBtnClick();

	UFUNCTION()
	void OnQuitBtnClick();

	UFUNCTION()
	void OnMainMenuBtnClick();

private:


	
};
