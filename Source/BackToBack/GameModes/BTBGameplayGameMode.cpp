// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGameplayGameMode.h"

#include "BackToBack/Actors/BTBCamera.h"
#include "BackToBack/Actors/BTBEnemySpawner.h"
#include "Camera/CameraActor.h"
#include "BackToBack/Pawns/BTBInputReceiverPawn.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/DataAssets/BTBSplitScreenDataAsset.h"
#include "BackToBack/HUD/BTBGameHUD.h"
#include "BackToBack/HUD/BTBGameoverHUD.h"
#include "BackToBack/HUD/BTBPauseMenuHUD.h"
#include "BackToBack/PlayerControllers/BTBPlayerController.h"
#include "Components/RetainerBox.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBEnemyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "BackToBack/Actors/BTBCamera.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"


ABTBGameplayGameMode::ABTBGameplayGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	GunOffsetPosition = FVector(-35, -50, 30);
}

void ABTBGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	CreatePlayers();
	SetupPlayersCommunication();
	CreateUIWidget();
	AssignCameras();
	CreateEnemySpawnerAndSetCenterOfPlayers();

	GetWorldTimerManager().SetTimer(
		IncreaseScoreTimerHandle,
		this,
		&ABTBGameplayGameMode::IncreaseScoreEverySecond,
		1,
		true
	);

	PlayerCharacterArray[0]->OnPlayerDeath.AddDynamic(this, &ABTBGameplayGameMode::DisplayGameoverHUD);
	PlayerCharacterArray[1]->OnPlayerDeath.AddDynamic(this, &ABTBGameplayGameMode::DisplayGameoverHUD);
	
}

void ABTBGameplayGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	BindEnemiesDeathEventToUpdateScore();

	if (PlayerCharacterArray[0]->GetbIsPaused() || PlayerCharacterArray[1]->GetbIsPaused())
	{
		DisplayPauseHUD(true);
	}
	else
	{
		DisplayPauseHUD(false);
	}
	
}


void ABTBGameplayGameMode::CreatePlayers()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr && PlayableCharOneClass != nullptr && PlayableCharTwoClass != nullptr))
	{
		return;
	}

	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStartArray);

	const FVector PS1_Location = PlayerStartArray[0]->GetActorLocation();
	const FRotator PS1_Rotation = PlayerStartArray[0]->GetActorRotation();

	const FVector PS2_Location = PlayerStartArray[1]->GetActorLocation();
	const FRotator PS2_Rotation = PlayerStartArray[1]->GetActorRotation();

	const TObjectPtr<ABTBPlayableCharacter> PlayerCharacterOne =
		World->SpawnActor<ABTBPlayableCharacter>(PlayableCharOneClass, PS1_Location, PS1_Rotation);

	const TObjectPtr<ABTBPlayableCharacter> PlayerCharacterTwo =
		World->SpawnActor<ABTBPlayableCharacter>(PlayableCharTwoClass, PS2_Location, PS2_Rotation);

	PlayerCharacterArray.AddUnique(PlayerCharacterOne);
	PlayerCharacterArray.AddUnique(PlayerCharacterTwo);

	if(InputReceiverArray.Num() >= 2)
	{
		InputReceiverArray[0]->PlayerCharacterPtr = PlayerCharacterArray[0];
		InputReceiverArray[1]->PlayerCharacterPtr = PlayerCharacterArray[1];
	}
}

void ABTBGameplayGameMode::SetupPlayersCommunication()
{
	if(ensure(PlayerCharacterArray.Num() == 2))
	{
		PlayerCharacterArray[0]->OtherPlayer = PlayerCharacterArray[1];
		PlayerCharacterArray[1]->OtherPlayer = PlayerCharacterArray[0];
	}
}

void ABTBGameplayGameMode::AssignCameras()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(SplitScreenClass != nullptr && World != nullptr && CameraClass != nullptr))
	{
		return;
	}
	
	if (SplitScreenClass->CameraMode == ECameraMode::SingleCamera)
	{
		InputReceiverArray[0]->PlayerCharacterPtr->RemoveCamera();
		InputReceiverArray[1]->PlayerCharacterPtr->RemoveCamera();

		SingleCameraPtr = World->SpawnActor<ABTBCamera>(CameraClass);
		
		UGameplayStatics::GetPlayerController(World, 0)->SetViewTargetWithBlend(SingleCameraPtr);
		UGameplayStatics::GetPlayerController(World, 1)->SetViewTargetWithBlend(SingleCameraPtr);

		GameWidget->MainScreenBox->SetEffectMaterial(nullptr);
		GameWidget->MainScreenImage->SetRenderOpacity(0.0f);
	}
	
	else if (SplitScreenClass->CameraMode == ECameraMode::SplitScreen)
	{
		CreateRenderTextures();
		SetSplitScreenTextureToMaterial();
	}
}

void ABTBGameplayGameMode::CreateRenderTextures()
{
	const FVector2d ScreenSize = GetScreenResolution();
	RenderTexture_1 = NewObject<UTextureRenderTarget2D>(this, UTextureRenderTarget2D::StaticClass());
	RenderTexture_1->InitAutoFormat(ScreenSize.X, ScreenSize.Y);
	
	RenderTexture_2 = NewObject<UTextureRenderTarget2D>(this, UTextureRenderTarget2D::StaticClass());
	RenderTexture_2->InitAutoFormat(ScreenSize.X, ScreenSize.Y);

	PlayerCharacterArray[0]->AssignRenderTextureToCamera(RenderTexture_1);
	PlayerCharacterArray[1]->AssignRenderTextureToCamera(RenderTexture_2);
}

void ABTBGameplayGameMode::CreateUIWidget()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	
	if(IsValid(BTBGameHUDWidgetClass))
	{
		GameWidget = Cast<UBTBGameHUD>(CreateWidget(World, BTBGameHUDWidgetClass));
		if (GameWidget)
		{
			GameWidget->AddToViewport();
		}
	}
}

void ABTBGameplayGameMode::IncreaseScoreEverySecond()
{
	TotalScore += 1 /*FMath::RandRange(5, 10)*/;
	GameWidget->SetScore(TotalScore);
}

void ABTBGameplayGameMode::BindEnemiesDeathEventToUpdateScore()
{
	for (const auto& Enemy: EnemySpawnerPtr->EnemiesArray)
	{
		Enemy->OnAIDeath.AddUniqueDynamic(this, &ABTBGameplayGameMode::UpdateScore);
	}
}

void ABTBGameplayGameMode::DisplayGameoverHUD()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!ensure(World != nullptr))
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Gameover HUD should be displayed"));
	if (IsValid(BTBGameoverHUDWidgetClass))
	{
		GameoverWidget = Cast<UBTBGameOverHUD>(CreateWidget(World, BTBGameoverHUDWidgetClass));
		if (GameoverWidget)
		{
			auto theScore = GameWidget->Score;
			GameoverWidget->SetScore(theScore);
			GameoverWidget->AddToViewport();
			UGameplayStatics::SetGamePaused(World, true);
			UGameplayStatics::RemovePlayer(PlayerControllerArray[1], true);
		}
	}
	
}

void ABTBGameplayGameMode::DisplayPauseHUD(const bool Visibility)
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!ensure(World != nullptr))
	{
		return;
	}

	if (Visibility)
	{
		if (IsValid(BTBPauseHUDWidgetClass))
		{
			PauseWidget = Cast<UBTBPauseMenuHUD>(CreateWidget(World, BTBPauseHUDWidgetClass));//New
			if (PauseWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("Pause menu HUD should be displayed"));
			
				PauseWidget->AddToViewport();
				UGameplayStatics::SetGamePaused(World, true);
			
				PlayerCharacterArray[0]->SetbIsPaused(false);
				PlayerCharacterArray[1]->SetbIsPaused(false);

			}
		}
	}
	else
	{
		if (PauseWidget != nullptr)
		{
			PauseWidget->RemoveFromParent();
		}
	}

}

void ABTBGameplayGameMode::SetSplitScreenTextureToMaterial() const
{
	if(!ensure(GameWidget != nullptr))
	{
		return;
	}

	const TObjectPtr<UMaterialInstanceDynamic> DynamicMI =
		UMaterialInstanceDynamic::Create(SplitScreenMaterialInstance, nullptr);
	
	DynamicMI->SetTextureParameterValue(TEXT("Texture1"), RenderTexture_1);
	DynamicMI->SetTextureParameterValue(TEXT("Texture2"), RenderTexture_2);
	GameWidget->MainScreenBox->SetEffectMaterial(DynamicMI);
	GameWidget->MainScreenImage->SetRenderOpacity(1.0f);
}

void ABTBGameplayGameMode::CreateEnemySpawnerAndSetCenterOfPlayers()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}

	EnemySpawnerPtr = World->SpawnActor<ABTBEnemySpawner>(EnemySpawnerClass);
	
	if(EnemySpawnerPtr)
	{
		const FVector PlayersCenter =
			(PlayerCharacterArray[0]->GetActorLocation() + PlayerCharacterArray[1]->GetActorLocation()) / 2;

		EnemySpawnerPtr->Center = PlayersCenter;
		EnemySpawnerPtr->Center.Z = 0;
	}
}

FVector2d ABTBGameplayGameMode::GetScreenResolution()
{
	FVector2D Result;
	
	Result.X = GSystemResolution.ResX;
	Result.Y = GSystemResolution.ResY;
	
	return Result;
}

FVector2D ABTBGameplayGameMode::GetGameViewportSize()
{
	FVector2D Result;
	
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	
	 return Result;
}

void ABTBGameplayGameMode::UpdateScore()
{
	GameWidget->PlayAnimation
	(
		GameWidget->ScaleIT,
		0.0f,
		1,
		EUMGSequencePlayMode::Forward,
		1,
		false
	);
	
	TotalScore += 10;
	GameWidget->SetScore(TotalScore);
}
