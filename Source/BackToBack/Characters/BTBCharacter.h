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
	ABTBCharacter();
	
	bool GetbStartJump()
	{
		return bStartJump;
	}
	
	void SetbStartJump(const bool Value)
	{
		bStartJump = Value;
	}

	UFUNCTION(BlueprintCallable)
	virtual float GetUserInput_X()
	{
		return UserInput_X;
	}

	virtual void SetUserInput_X(const float Value)
	{
		UserInput_X = Value;
	}

	float GetUserInput_Y()
	{
		return UserInput_Y;
	}

	virtual void SetUserInput_Y(const float Value)
	{
		UserInput_Y = Value;
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

	bool GetbIsPaused()
	{
		return bIsPaused;
	}

	void SetbIsPaused(const bool Value)
	{
		bIsPaused = Value;
	}

	UFUNCTION(BlueprintCallable)
	virtual bool GetbStartSwitching()
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
	bool bStartSwitching = false;
	float UserInput_X;

protected:

	
private:
	bool bStartJump = false;
	bool bStartShoot = false;
	bool bStartPool = false;
	bool bIsPaused = false;
	float UserInput_Y;
	
};