// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "BTBGameHUD.generated.h"

class URetainerBox;
class UOverlay;

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
	
protected:
	static FVector2d GetScreenResolution();
	virtual void NativeConstruct() override;

private:

	

public:
	
protected:
	
private:
	
};
