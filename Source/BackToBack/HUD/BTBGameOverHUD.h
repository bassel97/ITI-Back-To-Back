// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTBGameOverHUD.generated.h"


class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBGameOverHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetScore(UTextBlock* Value);
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Score = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnRestartButtonClick();

	UFUNCTION()
	void OnMainMenuButtonClick();
	
};
