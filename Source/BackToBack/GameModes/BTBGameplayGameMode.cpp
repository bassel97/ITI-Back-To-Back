// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGameplayGameMode.h"

#include "BackToBack/Actors/BTBEnemySpawner.h"
#include "Camera/CameraActor.h"
#include "BackToBack/Pawns/BTBInputReceiverPawn.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/DataAssets/BTBSplitScreenDataAsset.h"
#include "BackToBack/HUD/BTBGameHUD.h"
#include "BackToBack/PlayerControllers/BTBPlayerController.h"
#include "Components/RetainerBox.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BackToBack/Actors/BTBGun.h"
#include "Blueprint/UserWidget.h"


void ABTBGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();
	GunOffsetPosition = FVector(-35, -50, 30);

	CreatePlayers();
	SetupPlayersCommunication();
	CreateUIWidget();
	AssignCameras();
	AssignGunToPlayer();
	SetCenterOfPlayersInEnemySpawner();
}


void ABTBGameplayGameMode::CreatePlayers()
{
	UWorld* World = GetWorld();
	if(!ensure(World != nullptr && PlayableCharOneClass != nullptr
	 && PlayableCharTwoClass != nullptr))
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
		InputReceiverArray[0]->Set_PlayerCharacter(PlayerCharacterArray[0]);
		InputReceiverArray[1]->Set_PlayerCharacter(PlayerCharacterArray[1]);
	}


#if UE_EDITOR
	for(int i = 0 ; i < PlayerCharacterArray.Num() ; i++)
	{
		UKismetSystemLibrary::PrintString(World,
			FString::Printf(TEXT("PlayableCharacter[%i] = %s, Its InputReceiverPawn = %s"),
				i, *PlayerCharacterArray[i]->GetName(), *InputReceiverArray[i]->Get_PlayerCharacter()->GetName()));
	}
#endif
	
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
		InputReceiverArray[0]->Get_PlayerCharacter()->RemoveCamera();
		InputReceiverArray[1]->Get_PlayerCharacter()->RemoveCamera();

		const TObjectPtr<AActor>  Camera = World->SpawnActor<AActor>(CameraClass);
		UGameplayStatics::GetPlayerController(World, 0)->SetViewTarget(Camera);
		UGameplayStatics::GetPlayerController(World, 1)->SetViewTarget(Camera);

		GameWidget->MainScreenBox->SetEffectMaterial(nullptr);
		GameWidget->MainScreenImage->SetRenderOpacity(0.0f);
	}
	else
	{
		CreateRenderTextures();
		SetSplitScreenTextureToMaterial();
	}

#if UE_EDITOR
	for(int i = 0 ; i < PlayerControllerArray.Num() ; i++)
	{
		UKismetSystemLibrary::PrintString(World,
			FString::Printf(TEXT("PlayerControllerArray[%i] = %s, Its ViewTarget = %s"),
				i, *PlayerControllerArray[i]->GetName(), *PlayerControllerArray[i]->GetViewTarget()->GetName()));
	}
#endif
	
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

void ABTBGameplayGameMode::SetSplitScreenTextureToMaterial() const
{
	if(!ensure(GameWidget!=nullptr))
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

void ABTBGameplayGameMode::AssignGunToPlayer()
{
	Gun = GetWorld()->SpawnActor<ABTBGun>(GunClass);
	if (Gun)
	{
		Gun->AttachToComponent(PlayerCharacterArray[0]->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));

		PlayerCharacterArray[0]->SetGun(Gun);
		//PlayerCharacterArray[0]->bGunAttached = true;
	}
}

void ABTBGameplayGameMode::SetCenterOfPlayersInEnemySpawner()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}

	const TObjectPtr<ABTBEnemySpawner> EnemySpawner =
		Cast<ABTBEnemySpawner>(UGameplayStatics::GetActorOfClass(World, ABTBEnemySpawner::StaticClass()));

	if(!ensure(EnemySpawner != nullptr))
	{
		return;
	}

	FVector PlayersCenter = (PlayerCharacterArray[0]->GetActorLocation() + PlayerCharacterArray[1]->GetActorLocation()) / 2;
	
	EnemySpawner->Center = PlayersCenter;
	EnemySpawner->Center.Z = 0;

	PlayerCharacterArray[0]->GunSwitchPosition->SetRelativeLocation(PlayersCenter + GunOffsetPosition);
	PlayerCharacterArray[1]->GunSwitchPosition->SetRelativeLocation(PlayersCenter + (-GunOffsetPosition));

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
