// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPlayableCharacter.h"
#include "BTBMiniGameTwoPlayableCharacter.generated.h"

class ABTBSpear;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBMiniGameTwoPlayableCharacter : public ABTBPlayableCharacter
{
	GENERATED_BODY()

public:
	ABTBMiniGameTwoPlayableCharacter();
	void SetSpear(ABTBSpear* Spear);
	ABTBSpear* GetSpear();
	void Throw();
	void AttachSpearToPlayer();
	void Summon();
	UFUNCTION(BlueprintCallable)
	bool GetbIsAttacking();

	UFUNCTION(BlueprintCallable)
	void SetbIsAttacking(bool Value);

	UFUNCTION(BlueprintCallable)
	bool GetbIsDashing()
	{
		return bIsDashing;
	}

	UFUNCTION(BlueprintCallable)
	void SetbIsDashing(bool Value)
	{
		bIsDashing = Value;
	}
	
protected:
	virtual void BeginPlay() override;
	// virtual float GetUserInput_X() override;
	// virtual float GetUserInput_Y() override;
	virtual void Die() override;
	
	UFUNCTION()
	virtual void OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:

public:
	TObjectPtr<ABTBSpear> SpearActor;

	UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
	bool bIsThrowing;

	UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
	bool bIsSummoning;

	UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
	bool bSpearAttached;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Dash Meter")
	int32 DashMeter = 5;

	UPROPERTY()
	UAnimInstance* MilesAnimInstance;

protected:


private:
	UPROPERTY(EditAnywhere, Category = "Spear Retrieval Point")
		TObjectPtr<USceneComponent> SpearRetrievalPoint;
	
	bool bIsAttacking;

	bool bIsDashing;
};
