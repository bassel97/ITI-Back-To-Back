// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGun.h"
#include"BackToBack/Actors/BTBObjectPoolComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/MeshComponent.h"
#include "BackToBack/Actors/BTBPooledObject.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ChildActorComponent.h"

ABTBGun::ABTBGun()
{
	BulletPool = CreateDefaultSubobject<UBTBObjectPoolComponent>(TEXT("BulletPool"));
	AddOwnedComponent(BulletPool);

	ShootingLocation = CreateDefaultSubobject<UChildActorComponent>(TEXT("Shooting Location"));
	ShootingLocation->SetupAttachment(SceneComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(SceneComponent);

	GunSkeletal = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Skeleton"));
	GunSkeletal->SetupAttachment(SceneComponent);
}

void ABTBGun::Shoot()
{
	if(Ammo <= 5)
	{
		Bullet = BulletPool->SpawnPooledObject(ShootingLocation->GetComponentLocation(), BulletOrientation);
		Ammo++;
		UProjectileMovementComponent* BulletProjectile = NewObject<UProjectileMovementComponent>(Bullet, UProjectileMovementComponent::StaticClass(), TEXT("Projectile Movement"));
		Bullet->AddOwnedComponent(BulletProjectile);
		Bullet->FinishAddComponent(BulletProjectile, true, Bullet->GetActorTransform());
		if (!BulletProjectile)
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet Projectile is is not added"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet Projectile is added"));
			BulletProjectile->ProjectileGravityScale = 0.f;
			BulletProjectile->AddForce(GetActorForwardVector() * BulletVelocity );
			GunSkeletal->PlayAnimation(ShootingAnim, false);
		}
	}
	else
	{
		Ammo = 0;
		GunSkeletal->PlayAnimation(ReloadingAnim, false);
	}
	
}