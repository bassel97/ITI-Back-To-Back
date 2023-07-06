// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBAICharacter.h"
#include "BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/HUD/BTBGameHUD.h"
#include "Components/SphereComponent.h"
#include "BTBEnemyCharacter.generated.h"

class UBoxComponent;
class UBTBGameHUD;
class UNiagaraSystem;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBEnemyCharacter : public ABTBAICharacter
{
	GENERATED_BODY()

public:
	ABTBEnemyCharacter();
	void AttackPlayer();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Die() override;

	UFUNCTION(BlueprintCallable)
	void GetDamaged();
	
	void DestroyEnemy();

	UFUNCTION()
	void OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerGetCloser(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:

	bool bIsgettingDamaged;
	

public:
	UFUNCTION(BlueprintCallable)
	bool GetGettingDamaged();

	UFUNCTION(BlueprintCallable)
	void SetGettingDamaged(bool value);

	UFUNCTION(BlueprintPure)
	float CalculateHealthPercentage() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsAttackingPlayer()
	{
		return bIsAttacking;
	}

	UFUNCTION(BlueprintCallable)
	void SetIsAttackingPlayer(bool Value)
	{
		bIsAttacking = Value;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> CollisionBox;
	
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Animation | Death")
	TObjectPtr<UAnimationAsset> DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* DamageEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI | Health")
	UWidgetComponent* HealthWidgetComp;

private:
	FTimerHandle DestroyTimeHandle;
	
	bool bIsAttacking = false;
};

