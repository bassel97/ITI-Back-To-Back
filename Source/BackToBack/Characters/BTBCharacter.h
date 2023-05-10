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

	virtual void Tick(float DeltaTime) override;

	bool GetbStartJump();
	
	void SetbStartJump(bool Value);

	bool GetbStartRotate();

	void SetbStartRotate(bool Value);

	bool GetbStartMove();

	void SetbStartMove(bool Value);

	float GetRotationValue();

	void SetRotationValue(float Value);

	float GetMoveValue();

	void SetMoveValue(float Value);

	

	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UBTBCharacterAction>> CharacterActions;

private:
	bool bStartJump = false;

	bool bStartRotate = false;

	bool bStartMove = false;

	float RotationValue;

	float MoveValue;

	
};