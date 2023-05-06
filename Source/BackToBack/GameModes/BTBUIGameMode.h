// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "BTBUIGameMode.generated.h"

/**
 * Our Version of the mainmenu gamemode
 */
UCLASS()
class BACKTOBACK_API ABTBUIGameMode : public ABTBGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, Category = "Config")
		TSubclassOf<UUserWidget> BTBMainMenuWidgetClass;

	virtual void BeginPlay() override;
};
