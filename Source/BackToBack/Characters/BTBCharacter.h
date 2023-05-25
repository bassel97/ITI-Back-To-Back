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
	bool GetbStartJump()
	{
		return bStartJump;
	}
	
	void SetbStartJump(const bool Value)
	{
		bStartJump = Value;
	}

	UFUNCTION(BlueprintCallable)
	virtual float GetRotationValue()
	{
		return RotationValue;
	}

	void SetRotationValue(const float Value)
	{
		RotationValue = Value;
	}

	float GetMoveValue()
	{
		return MoveValue;
	}

	void SetMoveValue(const float Value)
	{
		MoveValue = Value;
	}

	bool GetbStartShoot()
	{
		return bStartShoot;
	}

	void SetbStartShoot(const bool Value)
	{
		bStartShoot = Value;
	}

	bool GetbStartPool()
	{
		return bStartPool;
	}

	void SetbStartPool(const bool Value)
	{
		bStartPool = Value;
	}

	UFUNCTION(BlueprintCallable)
	bool GetbStartSwitching()
	{
		return bStartSwitching;
	}

	UFUNCTION(BlueprintCallable)
	void SetbStartSwitching(const bool Value)
	{
		bStartSwitching = Value;
	}
	
protected:
	virtual void Die() PURE_VIRTUAL(ABTBCharacter::Die);
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	

	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UBTBCharacterAction>> CharacterActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 Health { 2 };

	bool bStartRotate = false;
	float RotationValue;

protected:

	
private:
	bool bStartJump = false;
	bool bStartShoot = false;
	bool bStartPool = false;
	bool bStartSwitching = false;
	float MoveValue;
	
};