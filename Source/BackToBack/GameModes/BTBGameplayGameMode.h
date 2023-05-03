// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameModeBase.h"
#include "BTBGameplayGameMode.generated.h"

class ABTBPlayableCharacter;
class UBTBSplitScreenDataAsset;
class UTextureRenderTarget2D;

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
	void CreateRenderTextures();

	static FVector2d GetScreenResolution();
	static FVector2D GetGameViewportSize();
	
private:

	
	
public:
	
protected:
	
private:
	TArray<TObjectPtr<ABTBPlayableCharacter>> PlayerCharacterArray;
	TArray<TObjectPtr<AActor>> PlayerStartArray;
	
	UPROPERTY(EditDefaultsOnly, Category = "GlobalGameScreen")
	TObjectPtr<UBTBSplitScreenDataAsset> SplitScreenClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="GlobalGameScreen")
	TSubclassOf<AActor> CameraClass;
	
    TObjectPtr<UTextureRenderTarget2D> RenderTexture_1;
	TObjectPtr<UTextureRenderTarget2D> RenderTexture_2;
};
