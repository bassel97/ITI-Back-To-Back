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
	UFUNCTION()
	void SetScore(int32 Value);

protected:
	virtual void NativeConstruct() override;
	
private:

	

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<URetainerBox> MainScreenBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> MainScreenImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Score = nullptr;
	
protected:
	
private:
	
};
