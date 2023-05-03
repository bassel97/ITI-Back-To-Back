// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BTBMainMenuGameMode.generated.h"

/**
 * Our Version of the mainmenu gamemode
 */
UCLASS()
class BACKTOBACK_API ABTBMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, Category = "Config")
		TSubclassOf<UUserWidget> BTBMainMenuWidgetClass;
	virtual void BeginPlay() override;
};
