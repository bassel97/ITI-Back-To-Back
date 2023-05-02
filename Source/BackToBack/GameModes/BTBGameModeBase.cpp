// Copyright di-tri studio, Inc. All Rights Reserved.


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
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr && BTBInputReceiverClass != nullptr))
	{
		return;
	}

	ABTBPlayerController* PlayerOne = Cast<ABTBPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	if (ensure(PlayerOne != nullptr))
	{
		ABTBInputReceiverPawn* SpawnedPlayer = World->SpawnActor<ABTBInputReceiverPawn>(BTBInputReceiverClass);

		// PLayer 1 (indexed with zero)
		SpawnedPlayer->PlayerIndex = 0;
		InputReceiverArray.AddUnique(SpawnedPlayer);

		PlayerControllerArray.AddUnique(PlayerOne);
		PlayerOne->Possess(SpawnedPlayer);
	}

	ABTBPlayerController* PlayerTwo = Cast<ABTBPlayerController>(UGameplayStatics::CreatePlayer(World, 1));
	if (ensure(PlayerTwo != nullptr))
	{
		ABTBInputReceiverPawn* SpawnedPlayer = World->SpawnActor<ABTBInputReceiverPawn>(BTBInputReceiverClass);
		
		// PLayer 2 (indexed with one)
		SpawnedPlayer->PlayerIndex = 1;
		InputReceiverArray.AddUnique(SpawnedPlayer);
			
		PlayerControllerArray.AddUnique(PlayerTwo);
		PlayerTwo->Possess(SpawnedPlayer);
	}

#if UE_EDITOR
	UKismetSystemLibrary::PrintString(World,TEXT("InputReceiverArray = " + FString::FromInt(InputReceiverArray.Num())));
	UKismetSystemLibrary::PrintString(World,TEXT("PlayerControllerArray = " + FString::FromInt(PlayerControllerArray.Num())));

	for(int i = 0 ; i < InputReceiverArray.Num() ; i++)
	{
		UKismetSystemLibrary::PrintString(World,
			FString::Printf(TEXT("InputReceiverArray[%i] = %s, Its Controller = %s"),
				i, *InputReceiverArray[i]->GetName(), *InputReceiverArray[i]->GetController()->GetName()));
	}
#endif	
}
