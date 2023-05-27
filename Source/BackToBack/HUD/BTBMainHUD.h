// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTBMainHUD.generated.h"

class UButton;

/**
 * Our version of the HUD MainMenu 
 */
UCLASS()
class BACKTOBACK_API UBTBMainHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnStartClick();

	UFUNCTION()
	void OnQuitClick();
	
private:


	
public:
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Start_BTN;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Quit_BTN;
	
private:
	
};
