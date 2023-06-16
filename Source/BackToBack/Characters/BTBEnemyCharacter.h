// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBAICharacter.h"
#include "BackToBack/HUD/BTBGameHUD.h"
#include "BTBEnemyCharacter.generated.h"

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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Die() override;

	UFUNCTION(BlueprintCallable)
	void GetDamaged();
	
	void DestroyEnemy();

	UFUNCTION()
	void OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:

	bool bIsgettingDamaged;
	

public:
	UFUNCTION(BlueprintCallable)
	bool GetGettingDamaged();

	UFUNCTION(BlueprintCallable)
	void SetGettingDamaged(bool value);

	UFUNCTION(BlueprintPure)
	float CalculateHealthPercentage() const;
	
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Animation | Death")
	TObjectPtr<UAnimationAsset> DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* DamageEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation | Damage")
	UAnimationAsset* DamageAnimation;

	//FTimerHandle TimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI | Health")
	UWidgetComponent* HealthWidgetComp;

private:
	FTimerHandle DestroyTimeHandle;

	// TObjectPtr<UMaterialInstanceDynamic> ClothMat;
	// TObjectPtr<UMaterialInstanceDynamic> BodyMat;
	//
	// UPROPERTY(EditDefaultsOnly, Category="Effect")
	// TObjectPtr<UNiagaraSystem> NiagaraDissolveDeathEffect;
};
