// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTBEnemyHealthBarHUD.generated.h"

class UProgressBar;

/**
 * Our Enemy Health Bar Hud for Mini Game Two Enemy Characters  
 */
UCLASS()
class BACKTOBACK_API UBTBEnemyHealthBarHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
protected:
	virtual void NativeConstruct() override;
	
private:


	
public:
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar;

private:
	
};
