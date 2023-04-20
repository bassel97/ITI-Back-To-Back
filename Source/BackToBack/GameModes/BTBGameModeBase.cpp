// Copyright Epic Games, Inc. All Rights Reserved.


#include "BTBGameModeBase.h"

#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/Pawns/BTBInputReceiverPawn.h"
#include "BackToBack/PlayerControllers/BTBPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

ABTBGameModeBase::ABTBGameModeBase()
{
	GameSessionClass = nullptr;
	GameStateClass = nullptr;
	PlayerControllerClass = nullptr;
	PlayerStateClass = nullptr;
	HUDClass = nullptr;
	DefaultPawnClass = nullptr;
	SpectatorClass = nullptr;
	ReplaySpectatorPlayerControllerClass = nullptr;
	ServerStatReplicatorClass = nullptr;
}

void ABTBGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetPlayerStartPoints();
	SpawnInputReceivers();
}

void ABTBGameModeBase::SpawnPlayer_Implementation(int32 CurrentPlayerIndex, ABTBInputReceiverPawn* InputReceiverPawn)
{
	IBTBGameModeInterface::SpawnPlayer_Implementation(CurrentPlayerIndex, InputReceiverPawn);
	UE_LOG(LogTemp, Warning, TEXT("SpawnPawn_Implementation"));

	if(UWorld* World = GetWorld())
	{
		const FTransform Transform = InputReceiverPawn->GetTransform();
		const ABTBPlayableCharacter* SpawnedPlayableCharacter =
			World->SpawnActor<ABTBPlayableCharacter>(ABTBPlayableCharacter::StaticClass(), Transform);
		
		SpawnedPlayableCharacter->Controller->Possess(InputReceiverPawn);
	}
}

void ABTBGameModeBase::SpawnPlayerPure(int32 CurrentPlayerIndex, ABTBInputReceiverPawn* InputReceiverPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnPawnPure"));

	if(UWorld* World = GetWorld())
	{
		const FTransform Transform = InputReceiverPawn->GetTransform();
		const ABTBPlayableCharacter* SpawnedPlayableCharacter =
			World->SpawnActor<ABTBPlayableCharacter>(ABTBPlayableCharacter::StaticClass(), Transform);
		
		SpawnedPlayableCharacter->Controller->Possess(InputReceiverPawn);
	}
}


void ABTBGameModeBase::GetPlayerStartPoints()
{
	if(const UWorld* World = GetWorld())
	{
		TArray<AActor*> ResultActors;
		UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), ResultActors);
		for (const auto Actor : ResultActors)
		{
			if(APlayerStart* PlayerStartActor = Cast<APlayerStart>(Actor))
			{
				PlayerStartArray.AddUnique(PlayerStartActor);
			}
		}
		UKismetSystemLibrary::PrintString(World,
			TEXT("PlayerStartArray = " + FString::FromInt(PlayerStartArray.Num())));
	}
}

void ABTBGameModeBase::SpawnInputReceivers()
{
	if(!PlayerStartArray.IsEmpty())
	{
		for(int i = 1 ; i < PlayerStartArray.Num() ; i++)
		{
			for(int j = 0 ; j < PlayerStartArray.Num() ; j++)
			{
				if(FCString::Atoi(*PlayerStartArray[j]->PlayerStartTag.ToString()) == i)
				{
					if(UWorld* World = GetWorld())
					{
						if(UGameplayStatics::CreatePlayer(World, i))
						{
							const FTransform Transform = PlayerStartArray[i]->GetTransform();
							ABTBInputReceiverPawn* SpawnedPlayer =
								World->SpawnActor<ABTBInputReceiverPawn>(BTBInputReceiverClass, Transform);
							
							SpawnedPlayer->PlayerIndex = i;
							PlayerInputReceiverArray.AddUnique(SpawnedPlayer);
							
							if(ABTBPlayerController* BtbPlayerController =
								Cast<ABTBPlayerController>(UGameplayStatics::GetPlayerController(World, SpawnedPlayer->PlayerIndex)))
							{
								PlayerControllerArray.AddUnique(BtbPlayerController);
								PlayerControllerArray[SpawnedPlayer->PlayerIndex - 1]->Possess(SpawnedPlayer);
							}
						}
					}
				}
			}
		}
		UKismetSystemLibrary::PrintString(GetWorld(),TEXT("PlayerInputReceiverArray = " + FString::FromInt(PlayerInputReceiverArray.Num())));
		UKismetSystemLibrary::PrintString(GetWorld(),TEXT("PlayerControllerArray = " + FString::FromInt(PlayerControllerArray.Num())));

		for(int i = 0 ; i < PlayerInputReceiverArray.Num() ; i++)
		{
			UKismetSystemLibrary::PrintString(GetWorld(),
				FString::Printf(TEXT("InputReceiverName = %s, Its Controller = %s"),
					*PlayerInputReceiverArray[i]->GetName(), *PlayerInputReceiverArray[i]->GetController()->GetName()));
		}

		for(int i = 0 ; i < PlayerControllerArray.Num() ; i++)
		{
			UKismetSystemLibrary::PrintString(GetWorld(),
				FString::Printf(TEXT("PlayerControllerArray[%i] = %s "), i, *PlayerControllerArray[i]->GetName()));
		}
	}
}

