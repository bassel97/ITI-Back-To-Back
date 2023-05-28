// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "BTBGameHUD.generated.h"

class URetainerBox;
class UOverlay;
class UTextBlock;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBGameHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URetainerBox> MainScreenBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> MainScreenImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UTextBlock> Score;
	UFUNCTION()
		void SetScore(int32 ScoreValue);

	/*UFUNCTION()
		void InitializeHud(AEndlessRunnerGameModeBase* RunGameMode);*/
protected:
	virtual void NativeConstruct() override;

	
private:

	

public:
	
protected:
	
private:
	
};
