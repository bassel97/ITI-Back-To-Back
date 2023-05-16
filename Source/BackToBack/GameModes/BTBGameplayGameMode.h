// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "BTBGameplayGameMode.generated.h"

class ABTBPlayableCharacter;
class UBTBSplitScreenDataAsset;
class UTextureRenderTarget2D;
class UBTBGameHUD;
class ABTBGun;

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
	void CreateUIWidget();
	void SetSplitScreenTextureToMaterial() const;
	void AssignGunToPlayer();

	static FVector2d GetScreenResolution();
	static FVector2D GetGameViewportSize();
	
private:

	
	
public:
	
protected:
	
private:
	TArray<TObjectPtr<ABTBPlayableCharacter>> PlayerCharacterArray;
	TArray<TObjectPtr<AActor>> PlayerStartArray;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABTBPlayableCharacter> PlayableCharOneClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABTBPlayableCharacter> PlayableCharTwoClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "GlobalGameScreen")
	TObjectPtr<UBTBSplitScreenDataAsset> SplitScreenClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="GlobalGameScreen")
	TSubclassOf<AActor> CameraClass;
	
    TObjectPtr<UTextureRenderTarget2D> RenderTexture_1;
	TObjectPtr<UTextureRenderTarget2D> RenderTexture_2;

	UPROPERTY(EditAnyWhere, Category = "Config")
	TSubclassOf<UUserWidget> BTBGameHUDWidgetClass;

	TObjectPtr<UBTBGameHUD> GameWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UMaterialInstance> SplitScreenMaterialInstance;

	UPROPERTY(EditDefaultsOnly, Category="Player Weapons")
		TSubclassOf<ABTBGun> GunClass;

	TObjectPtr<ABTBGun> Gun;
};
