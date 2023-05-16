// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGun.h"
#include"BackToBack/Actors/BTBObjectPoolComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/MeshComponent.h"
#include "BackToBack/Actors/BTBPooledObject.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ABTBGun::ABTBGun()
{
	BulletPool = CreateDefaultSubobject<UBTBObjectPoolComponent>(TEXT("BulletPool"));
	AddOwnedComponent(BulletPool);

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(SceneComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereCollider"));
	CollisionBox->SetupAttachment(SceneComponent);

	GunSkeletal = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Skeleton"));
	GunSkeletal->SetupAttachment(GunMesh);
}

void ABTBGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABTBGun::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABTBGun::Shoot()
{
	Bullet = BulletPool->SpawnPooledObject(SpawnPosition,BulletOrientation);
	
	UProjectileMovementComponent* BulletProjectile = Bullet->CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	BulletProjectile->ProjectileGravityScale = 0.f;
	BulletProjectile->Velocity = this->GetActorForwardVector() * BulletVelocity;
	
}

void ABTBGun::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetIsOverlapping(true);
}

void ABTBGun::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetIsOverlapping(false);
}

bool ABTBGun::GetbIsOverlapping()
{
	return bIsOverlapping;
}

void ABTBGun::SetIsOverlapping(bool Value)
{
	bIsOverlapping = Value;
}