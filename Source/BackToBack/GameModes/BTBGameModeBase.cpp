// Copyright Epic Games, Inc. All Rights Reserved.


#include "BTBGameModeBase.h"

#include "BackToBack/Pawns/BTBInputReceiverPawn.h"
#include "BackToBack/PlayerControllers/BTBPlayerController.h"
#include "Kismet/GameplayStatics.h"


void ABTBGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnInputReceivers();
}

void ABTBGameModeBase::SpawnInputReceivers()
{
	if(UWorld* World = GetWorld())
	{
		/**
		* Hard coding the first "InputReceiverPawn" spawning, cuz our BP_BTBGameModeBase has a DefaultPawnClass = None. 
		* @see BP_BTBGameModeBase in Unreal Engine's Content Browser
		*/
		ABTBInputReceiverPawn* SpawnedPlayerAsDefaultWithIndexZero = World->SpawnActor<ABTBInputReceiverPawn>(BTBInputReceiverClass);
		InputReceiverArray.AddUnique(SpawnedPlayerAsDefaultWithIndexZero);

		/** Then we create another InputReceiverPawns & A BTBPlayerController for it. */
		if(UGameplayStatics::CreatePlayer(World, 1))
		{
			ABTBInputReceiverPawn* SpawnedPlayer = World->SpawnActor<ABTBInputReceiverPawn>(BTBInputReceiverClass);
		
			SpawnedPlayer->PlayerIndex = 1;
			InputReceiverArray.AddUnique(SpawnedPlayer);
			
			if(ABTBPlayerController* BtbPlayerController =
				Cast<ABTBPlayerController>(UGameplayStatics::GetPlayerController(World, SpawnedPlayer->PlayerIndex)))
			{
				PlayerControllerArray.AddUnique(BtbPlayerController);
				PlayerControllerArray[SpawnedPlayer->PlayerIndex - 1]->Possess(SpawnedPlayer);
			}
		}
		
		/** Get all BTBPlayerControllers & Add them to our PlayerControllerArray. */
		TArray<AActor*> ResultControllers;
		UGameplayStatics::GetAllActorsOfClass(World, ABTBPlayerController::StaticClass(), ResultControllers);
		for (const auto Controller : ResultControllers)
		{
			if(auto CastedController = Cast<ABTBPlayerController>(Controller))
			{
				PlayerControllerArray.AddUnique(CastedController);
			}
		}

		/** Get the last element, put it as the first one, shift all elements by 1. */
		if (PlayerControllerArray.Num() > 1)
		{
			PlayerControllerArray.Insert(PlayerControllerArray.Pop(), 0);
		}

		/** Each controller can now posses its corresponding input receiver safely. */
		if(PlayerControllerArray.Num() == InputReceiverArray.Num())
		{
			for (int i = 0; i < PlayerControllerArray.Num(); i++)
			{
				PlayerControllerArray[i]->Possess(InputReceiverArray[i]);
			}
		}
	}


#if UE_EDITOR
		UKismetSystemLibrary::PrintString(GetWorld(),TEXT("InputReceiverArray = " + FString::FromInt(InputReceiverArray.Num())));
		UKismetSystemLibrary::PrintString(GetWorld(),TEXT("PlayerControllerArray = " + FString::FromInt(PlayerControllerArray.Num())));

		for(int i = 0 ; i < InputReceiverArray.Num() ; i++)
		{
			UKismetSystemLibrary::PrintString(GetWorld(),
				FString::Printf(TEXT("InputReceiverArray[%i] = %s, Its Controller = %s"),
					i, *InputReceiverArray[i]->GetName(), *InputReceiverArray[i]->GetController()->GetName()));
		}
#endif
	
}
