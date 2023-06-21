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

	GunAnim = GunSkeletal->GetAnimInstance();
}

void ABTBGun::Shoot(const FVector Direction)
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
			UE_LOG(LogTemp, Warning, TEXT("Bullet Projectile is not added"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet Projectile is added"));
			GunSkeletal->PlayAnimation(ShootingAnim, false);
			/*if(GunAnim->WasAnimNotifyNameTriggeredInAnyState(FName("BulletInstance")))
			{
				UE_LOG(LogTemp, Warning, TEXT("Bullet is instantiated"));
				BulletProjectile->ProjectileGravityScale = 0.f;
				BulletProjectile->AddForce(Direction * BulletVelocity);
			}*/
			// TArray<AActor*> ActorsToIgnore;
			// FHitResult HitRes;
			// bool bHitTrace = UKismetSystemLibrary::LineTraceSingle
			// (
			// 	GetWorld(),
			// 	ShootingLocation->GetComponentToWorld().GetLocation(),
			// 	FVector(ShootingLocation->GetComponentToWorld().GetLocation().X + 10000.f,0.f,0.f),
			// 	TraceTypeQuery1,
			// 	false,
			// 	ActorsToIgnore,
			// 	EDrawDebugTrace::ForDuration,
			// 	HitRes,
			// 	true,
			// 	FColor::Red,
			// 	FColor::Green,
			// 	5.f
			// );
			// if(bHitTrace)
			// {
			// 	if(HitRes.GetActor())
			// 	{
			// 		if(Cast<APawn*>(HitRes))
			// 	}
			// }
			BulletProjectile->ProjectileGravityScale = 0.f;
			BulletProjectile->AddForce(Direction * BulletVelocity );
			GunSkeletal->PlayAnimation(ShootingAnim, false);
		}
	}
	else
	{
		Ammo = 0;
		GunSkeletal->PlayAnimation(ReloadingAnim, false);
	}
	
}