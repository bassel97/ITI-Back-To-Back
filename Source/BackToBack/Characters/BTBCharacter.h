// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BTBCharacter.generated.h"


class UBTBCharacterAction;

/**
 * Our Version of Character.
 */

UCLASS()
class BACKTOBACK_API ABTBCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	bool GetbStartJump();
	
	void SetbStartJump(bool bStartJump);


private:
	bool bStartJump = false;

	UPROPERTY(EditDefaultsOnly)
	TArray<UBTBCharacterAction*> CharacterActions;

};