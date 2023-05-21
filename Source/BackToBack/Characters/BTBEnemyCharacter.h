// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBAICharacter.h"
#include "BTBEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBEnemyCharacter : public ABTBAICharacter
{
	GENERATED_BODY()


protected:
	virtual void Die() override;
	virtual void BeginPlay() override;
	void Damage();
	void DestroyEnemy();
	UPROPERTY(EditAnywhere,Category="Death Animation")
		TObjectPtr<UAnimationAsset> DeathAnimation;
	/*UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimMontage> DeathAnimationMontage;*/
	UFUNCTION()
		void OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	FTimerHandle DestroyTimeHandle;
};
