// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBWeaponBase.h"
#include "BTBGun.generated.h"

class ABTBPooledObject;
class USkeletalMeshComponent;
class UMeshComponent;
class UProjectileMovementComponent;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBGun : public ABTBWeaponBase 
{
	GENERATED_BODY()

public:
	ABTBGun();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBTBObjectPoolComponent* BulletPool;
	
	ABTBPooledObject* Bullet;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	FRotator BulletOrientation;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float BulletVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* GunSkeletal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UChildActorComponent* ShootingLocation;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimationAsset> ShootingAnim;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UAnimationAsset> ReloadingAnim;

	//bool GetbIsOverlapping();

	//void SetIsOverlapping(bool Value);

	void Shoot();

protected:

	//UFUNCTION()
	//	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//     
private:

	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//bool bIsOverlapping;

	TSubclassOf<UProjectileMovementComponent> ProjectileComponent;
	int32 Ammo{ 0 };
};
