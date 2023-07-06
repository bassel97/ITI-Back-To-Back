// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBWeaponBase.h"
#include "BTBSpear.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class URotatingMovementComponent;
class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UPointLightComponent;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBSpear : public ABTBWeaponBase
{
	GENERATED_BODY()

public:
	ABTBSpear();

	void Throw(const FVector& Direction, const float Speed);

	void Summon(AActor* SummoningLocation);

	void ActivateBoxCollision();

	void DeactivateBoxCollision();

	void SetPointLightColorAndIntensity(FLinearColor Color, float Intensity);

	void ResetSpearPhysics();

protected:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	void StopSpearBounce(AActor* SpearNewParentActor);

	void Fall(float GravityScale);
	
	void BounceAtEnemies();

	void HomingFunction(bool bIsHoming, float InitialSpeed, float MaxSpeed, float HomingAcceleration, AActor* Target);

	

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PerformSphereTrace(const FVector& StartLocation, const FVector& EndLocation, float Radius, TArray<AActor*> Target);

public:

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> BoxTraceEnd;
	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		TObjectPtr<UNiagaraComponent> SpearVFX;

	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		TObjectPtr<UPointLightComponent> SpearPointLight;

	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		TObjectPtr<UNiagaraSystem> SpearThrowVFX;

	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		FLinearColor SpearInHandColor;

	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		float ThrowGravityScale;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
		float SpearSpeed;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TObjectPtr<UStaticMeshComponent> SpearMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Components")
		TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

private:
	
	TMap<AActor*,bool> EnemiesArray;

	bool bIsAttached = true;

	bool bIsSummoning = false;

	int32 EnemyCounter = 0;
	int32 SphereTraceDebug = 0;

	


};
