// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameModeBase.h"
#include "BTBGameplayGameMode.generated.h"

class ABTBPlayableCharacter;
class UBTBSplitScreenDataAsset;

/**
 * Our Gameplay Game Mode
 */
UCLASS()
class BACKTOBACK_API ABTBGameplayGameMode final : public ABTBGameModeBase
{
	GENERATED_BODY()

public:
	
protected:
	virtual void BeginPlay() override;
	void CreatePlayers();
	void AssignCameras();
	
private:

	
	
public:
	
protected:
	
private:
	TArray<ABTBPlayableCharacter*> PlayerCharacterArray;
	TArray<AActor*> PlayerStartArray;
	UPROPERTY(EditDefaultsOnly, Category="GlobalGameScreen")
	TObjectPtr<UBTBSplitScreenDataAsset> SplitScreenClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="GlobalGameScreen")
	TSubclassOf<AActor> CameraClass;
};
