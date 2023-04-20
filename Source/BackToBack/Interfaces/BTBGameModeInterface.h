// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BTBGameModeInterface.generated.h"

class ABTBInputReceiverPawn;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBTBGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Our Version of Interface
 */
class BACKTOBACK_API IBTBGameModeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void SpawnPlayer(int32 CurrentPlayerIndex, ABTBInputReceiverPawn* InputReceiverPawn);

	UFUNCTION()
	virtual void SpawnPlayerPure(int32 CurrentPlayerIndex, ABTBInputReceiverPawn* InputReceiverPawn) = 0;
	
};
