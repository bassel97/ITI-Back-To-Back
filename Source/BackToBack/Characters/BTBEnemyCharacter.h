// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBAICharacter.h"
#include "BackToBack/HUD/BTBGameHUD.h"
#include "BTBEnemyCharacter.generated.h"

class UBTBGameHUD;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBEnemyCharacter : public ABTBAICharacter
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;
	virtual void Die() override;

	UFUNCTION(BlueprintCallable)
	void Damage();
	
	void DestroyEnemy();

	UFUNCTION()
	void OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:

	

public:
	
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Death Animation")
	TObjectPtr<UAnimationAsset> DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sound")
	USoundBase* sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* DeathEffect;


private:
	FTimerHandle DestroyTimeHandle;

};
