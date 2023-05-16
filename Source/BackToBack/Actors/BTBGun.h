// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBWeaponBase.h"
#include "BTBGun.generated.h"

class ABTBPooledObject;

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
	UPROPERTY(EditAnywhere, Category = "Bullets")
		ABTBPooledObject* Bullet;
	UPROPERTY(EditAnywhere, Category = "Bullet")
		FVector SpawnPosition;
	UPROPERTY(EditAnywhere, Category = "Bullet")
		FRotator BulletOrientation;
	UPROPERTY(EditAnywhere, Category = "Bullet")
		float BulletVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* CollisionBox;

	bool GetbIsOverlapping();

	void SetIsOverlapping(bool Value);

	void Shoot();

protected:

	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	     
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		bool bIsOverlapping;
};
