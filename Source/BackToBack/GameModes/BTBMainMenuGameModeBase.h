// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BTBMainMenuGameModeBase.generated.h"

/**
 * Our Version of MainMenu GameMode
 */
UCLASS()
class BACKTOBACK_API ABTBMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, Category = "Config")
		TSubclassOf<UUserWidget> BTBMainMenuWidgetClass;
	virtual void BeginPlay() override;
};
