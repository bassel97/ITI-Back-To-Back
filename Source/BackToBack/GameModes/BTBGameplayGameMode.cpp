// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGameplayGameMode.h"

#include "Camera/CameraActor.h"
#include "BackToBack/Pawns/BTBInputReceiverPawn.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/DataAssets/BTBSplitScreenDataAsset.h"
#include "BackToBack/PlayerControllers/BTBPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ABTBGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();
	CreatePlayers();
	AssignCameras();
}

void ABTBGameplayGameMode::CreatePlayers()
{
	UWorld* World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	
	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStartArray);
	
	ABTBPlayableCharacter* PlayerCharacterOne = World->SpawnActor<ABTBPlayableCharacter>();
	PlayerCharacterArray.AddUnique(PlayerCharacterOne);

	ABTBPlayableCharacter* PlayerCharacterTwo = World->SpawnActor<ABTBPlayableCharacter>();
	PlayerCharacterArray.AddUnique(PlayerCharacterTwo);

	if(PlayerStartArray.Num() >= 2)
	{
		PlayerCharacterOne->SetActorLocation(PlayerStartArray[0]->GetActorLocation());
		PlayerCharacterTwo->SetActorLocation(PlayerStartArray[1]->GetActorLocation());
	}

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

void ABTBGameplayGameMode::AssignCameras()
{
	UWorld* World = GetWorld();
	if(!ensure(SplitScreenClass != nullptr && World != nullptr && CameraClass != nullptr))
	{
		return;
	}
	
	if (SplitScreenClass->CameraMode == ECameraMode::SingleCamera)
	{
		InputReceiverArray[0]->Get_PlayerCharacter()->RemoveCamera();
		InputReceiverArray[1]->Get_PlayerCharacter()->RemoveCamera();

		AActor* Camera = World->SpawnActor<AActor>(CameraClass);
		UGameplayStatics::GetPlayerController(World, 0)->SetViewTarget(Camera);
		UGameplayStatics::GetPlayerController(World, 1)->SetViewTarget(Camera);
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
