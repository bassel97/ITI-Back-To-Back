// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameModeBase.h"
#include "BTBGameplayGameMode.generated.h"

class ABTBPlayableCharacter;
class UBTBSplitScreenDataAsset;
class UTextureRenderTarget2D;
class UBTBGameHUD;
class UBTBGameOverHUD;
class UBTBPauseMenuHUD;
class ABTBGun;
class UUserWidget;
class ABTBEnemySpawner;
class ABTBEnemyCharacter;

/**
 * Our Gameplay Game Mode
 */
UCLASS()
class BACKTOBACK_API ABTBGameplayGameMode : public ABTBGameModeBase
{
	GENERATED_BODY()

public:
	ABTBGameplayGameMode();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void CreatePlayers();
	void SetupPlayersCommunication();
	void AssignCameras();
	void CreateRenderTextures();
	void CreateUIWidget();
	void IncreaseScoreEveryOneSecond();

	void BindEnemiesDeathEventToUpdateScore();

	void SetSplitScreenTextureToMaterial() const;
	void CreateEnemySpawnerAndSetCenterOfPlayers();

	static FVector2D GetScreenResolution();
	static FVector2D GetGameViewportSize();

	
	UFUNCTION()
	void DisplayGameoverHUD();

	UFUNCTION()
	void DisplayPauseHUD();
	
	UFUNCTION()
	void UpdateScore();
	
private:
	
	
	
public:
	
protected:
	TArray<TObjectPtr<ABTBPlayableCharacter>> PlayerCharacterArray;
	TArray<TObjectPtr<AActor>> PlayerStartArray;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABTBPlayableCharacter> PlayableCharOneClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABTBPlayableCharacter> PlayableCharTwoClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABTBEnemySpawner> EnemySpawnerClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "GlobalGameScreen")
	TObjectPtr<UBTBSplitScreenDataAsset> SplitScreenClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "GlobalGameScreen")
	TSubclassOf<AActor> CameraClass;
	
	TObjectPtr<UTextureRenderTarget2D> RenderTexture_1;
	TObjectPtr<UTextureRenderTarget2D> RenderTexture_2;

	UPROPERTY(EditAnyWhere, Category = "Config")
	TSubclassOf<UUserWidget> BTBGameHUDWidgetClass;

	TObjectPtr<UBTBGameHUD> GameWidget;

	UPROPERTY(EditAnyWhere, Category = "Config")
	TSubclassOf<UUserWidget> BTBGameoverHUDWidgetClass;

	TObjectPtr<UBTBGameOverHUD> GameoverWidget;

	UPROPERTY(EditAnyWhere, Category = "Config")
	TSubclassOf<UUserWidget> BTBPauseHUDWidgetClass;

	TObjectPtr<UBTBPauseMenuHUD> PauseWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UMaterialInstance> SplitScreenMaterialInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Gun Position")
	FVector GunOffsetPosition;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	TSubclassOf<ABTBEnemyCharacter> EnemyClass;
	
	TObjectPtr<ABTBEnemySpawner> EnemySpawnerPtr;

	int32 TotalScore = 0;

	FTimerHandle IncreaseScoreTimerHandle;
	
private:

};
