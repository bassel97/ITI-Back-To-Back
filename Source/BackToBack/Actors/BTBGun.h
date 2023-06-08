// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBWeaponBase.h"
#include "BTBGun.generated.h"

class UBTBObjectPoolComponent;
class ABTBPooledObject;
class USkeletalMeshComponent;
class UMeshComponent;
class UProjectileMovementComponent;
class UBoxComponent;
class UChildActorComponent;
class UAnimationAsset;
class UAnimInstance;

/**
 * The player's gun base class
 */
UCLASS()
class BACKTOBACK_API ABTBGun : public ABTBWeaponBase 
{
	GENERATED_BODY()

public:
	ABTBGun();
	
	void Shoot(const FVector Direction);
	
protected:

private:


	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBTBObjectPoolComponent> BulletPool;

	TObjectPtr<ABTBPooledObject> Bullet;
	
	UPROPERTY(EditAnywhere, Category = "Bullet")
	FRotator BulletOrientation;
	
	UPROPERTY(EditAnywhere, Category = "Bullet")
	float BulletVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> GunSkeletal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UChildActorComponent> ShootingLocation;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimationAsset> ShootingAnim;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimationAsset> ReloadingAnim;

	UPROPERTY()
		UAnimInstance* GunAnim;
protected:
	
private:
	TSubclassOf<UProjectileMovementComponent> ProjectileComponent;
	int32 Ammo{ 0 };
	
};
