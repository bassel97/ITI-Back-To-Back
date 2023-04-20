// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Interfaces/BTBGameModeInterface.h"
#include "BackToBack/PlayerControllers/BTBPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "BTBGameModeBase.generated.h"

class APlayerStart;

/**
 * Our Version of GameModeBase.
 */
UCLASS()
class BACKTOBACK_API ABTBGameModeBase : public AGameModeBase, public IBTBGameModeInterface
{
	GENERATED_BODY()

public:
	virtual void SpawnPlayer_Implementation(int32 CurrentPlayerIndex, ABTBInputReceiverPawn* InputReceiverPawn) override;
	virtual void SpawnPlayerPure(int32 CurrentPlayerIndex, ABTBInputReceiverPawn* InputReceiverPawn) override;


protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void GetPlayerStartPoints();

	UFUNCTION()
	void SpawnInputReceivers();
	
private:
	TArray<APlayerStart*> PlayerStartArray;
	TArray<ABTBInputReceiverPawn*> PlayerInputReceiverArray;
	TArray<ABTBPlayerController*> PlayerControllerArray;

	UPROPERTY(EditAnywhere, Category="InputReceiver")
	TSubclassOf<ABTBInputReceiverPawn> BTBInputReceiverClass;
};
