// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPlayableCharacter.h"
#include "BTBMiniGameOnePlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBMiniGameOnePlayableCharacter : public ABTBPlayableCharacter
{
	GENERATED_BODY()

public:

	ABTBMiniGameOnePlayableCharacter();
	void SetGun(ABTBGun* Gun);
	ABTBGun* GetGun();



protected:
	virtual void BeginPlay() override;
	virtual float GetRotationValue() override;

	
	virtual void Die() override;

	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TObjectPtr<UChildActorComponent> GunSwitchPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		bool bGunAttached;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		bool IsOverlapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float ControlHandAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage")
		TObjectPtr<UAnimMontage> SwitchMontage;

	

	TObjectPtr<ABTBGun> GunActor;
};
