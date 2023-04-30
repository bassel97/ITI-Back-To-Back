// Copyright di-tri studio, Inc. All Rights Reserved.

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
	
protected:
	virtual void BeginPlay() override;
	void SpawnInputReceivers();
	
private:

	
	
public:
	
protected:
	TArray<ABTBInputReceiverPawn*> InputReceiverArray;
	TArray<ABTBPlayerController*> PlayerControllerArray;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "InputReceiver")
	TSubclassOf<ABTBInputReceiverPawn> BTBInputReceiverClass;

};
