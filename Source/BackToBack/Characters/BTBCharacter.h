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
	

public:

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	bool GetbStartJump()
	{
		return bStartJump;
	}
	
	void SetbStartJump(bool Value)
	{
		bStartJump = Value;
	}

	bool GetbStartRotate()
	{
		return bStartRotate;
	}

	void SetbStartRotate(bool Value)
	{
		bStartRotate = Value;
	}

	bool GetbStartMove()
	{
		return bStartMove;
	}


	void SetbStartMove(bool Value)
	{
		bStartMove = Value;
	}

	float GetRotationValue()
	{
		return RotationValue;
	}

	void SetRotationValue(float Value)
	{
		RotationValue = Value;

	}

	float GetMoveValue()
	{
		return MoveValue;
	}

	void SetMoveValue(float Value)
	{
		MoveValue = Value;
	}

	bool GetbStartShoot()
	{
		return bStartShoot;
	}

	void SetbStartShoot(bool Value)
	{
		bStartShoot = Value;
	}

	bool GetbStartPool()
	{
		return bStartPool;
	}

	void SetbStartPool(bool Value)
	{
		bStartPool = Value;
	}

	bool GetbStartSwitching()
	{
		return bStartSwitching;
	}

	void SetbStartSwitching(bool Value)
	{
		bStartSwitching = Value;
	}

	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UBTBCharacterAction>> CharacterActions;

private:
	bool bStartJump = false;

	bool bStartRotate = false;

	bool bStartMove = false;

	bool bStartShoot = false;

	bool bStartPool = false;

	bool bStartSwitching = false;

	float RotationValue;

	float MoveValue;

	
};