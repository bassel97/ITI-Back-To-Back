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
	bool bStartRotate = false;
	float RotationValue;

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

	virtual float GetRotationValue()
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
protected:
	virtual void Die() PURE_VIRTUAL(ABTBCharacter::Die);
public:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 Health {
		2
	};
private:
	bool bStartJump = false;
	
	bool bStartShoot = false;

	bool bStartPool = false;

	bool bStartSwitching = false;

	float MoveValue;

	
};