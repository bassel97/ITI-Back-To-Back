// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameModeBase.h"
#include "BTBGameplayGameMode.generated.h"

class ABTBPlayableCharacter;
class UBTBSplitScreenDataAsset;
class UTextureRenderTarget2D;
class UBTBGameHUD;
class ABTBGun;
class UUserWidget;

/**
 * Our Gameplay Game Mode
 */
UCLASS()
class BACKTOBACK_API ABTBGameplayGameMode : public ABTBGameModeBase
{
	GENERATED_BODY()

public:
	
protected:
	virtual void BeginPlay() override;
	void CreatePlayers();
	void SetupPlayersCommunication();
	void AssignCameras();
	void CreateRenderTextures();
	void CreateUIWidget();
	void SetSplitScreenTextureToMaterial() const;
	void SetCenterOfPlayersInEnemySpawner();

	static FVector2d GetScreenResolution();
	static FVector2D GetGameViewportSize();
	
private:

	
	
public:
	
protected:
	TArray<TObjectPtr<ABTBPlayableCharacter>> PlayerCharacterArray;
	TArray<TObjectPtr<AActor>> PlayerStartArray;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player mid point")
	FVector playersMidPoin;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABTBPlayableCharacter> PlayableCharOneClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABTBPlayableCharacter> PlayableCharTwoClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "GlobalGameScreen")
	TObjectPtr<UBTBSplitScreenDataAsset> SplitScreenClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "GlobalGameScreen")
	TSubclassOf<AActor> CameraClass;
	
	TObjectPtr<UTextureRenderTarget2D> RenderTexture_1;
	TObjectPtr<UTextureRenderTarget2D> RenderTexture_2;

	UPROPERTY(EditAnyWhere, Category = "Config")
	TSubclassOf<UUserWidget> BTBGameHUDWidgetClass;

	TObjectPtr<UBTBGameHUD> GameWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UMaterialInstance> SplitScreenMaterialInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Player Weapons")
	TSubclassOf<ABTBGun> GunClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Gun Position")
	FVector GunOffsetPosition;

	TObjectPtr<ABTBGun> Gun;
	
private:

};
