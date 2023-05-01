// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BTBCharacter.generated.h"


class UBTBCharacterAction;
class UInputMappingContext;

/**
 * Our Version of Character.
 */

UCLASS()
class BACKTOBACK_API ABTBCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	bool bCanJump;
	
	bool bCanMove;

	virtual void Tick(float DeltaTime) override;

	TArray<UBTBCharacterAction*> CharacterActions;
	
};