// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BTBGameModeBase.generated.h"

class APlayerStart;
class ABTBInputReceiverPawn;
class ABTBPlayerController;

/**
 * Our Version of GameModeBase.
 */
UCLASS()
class BACKTOBACK_API ABTBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	
public:


	
private:
	TArray<ABTBInputReceiverPawn*> InputReceiverArray;
	TArray<ABTBPlayerController*> PlayerControllerArray;

	UPROPERTY(EditAnywhere, Category="InputReceiver")
	TSubclassOf<ABTBInputReceiverPawn> BTBInputReceiverClass;


	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnInputReceivers();
	
};
