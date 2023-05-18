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

	ShootingLocation = CreateDefaultSubobject<UChildActorComponent>(TEXT("Shooting Location"));
	ShootingLocation->SetupAttachment(SceneComponent);

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(SceneComponent);

	GunSkeletal = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Skeleton"));
	GunSkeletal->SetupAttachment(GunMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	CollisionBox->SetupAttachment(GunSkeletal);
	CollisionBox->SetAllMassScale(0.5f);
}

void ABTBGun::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABTBGun::OnBoxOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABTBGun::OnBoxEndOverlap);
}

void ABTBGun::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABTBGun::Shoot()
{
	Bullet = BulletPool->SpawnPooledObject(ShootingLocation->GetComponentLocation(),BulletOrientation);
	
	
	UProjectileMovementComponent* BulletProjectile = NewObject<UProjectileMovementComponent>(Bullet, UProjectileMovementComponent::StaticClass(), TEXT("Projectile Movement"));
	Bullet->AddOwnedComponent(BulletProjectile);
	Bullet->FinishAddComponent(BulletProjectile,true, Bullet->GetActorTransform());
	if(!BulletProjectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet Projectile is is not added"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet Projectile is added"));
		BulletProjectile->ProjectileGravityScale = 0.f;
		/*BulletProjectile->InitialSpeed = 1300.f;
		BulletProjectile->MaxSpeed = 2000.f;*/
		BulletProjectile->AddForce(GetActorForwardVector() * 5000.f);
	}
	
	
}

void ABTBGun::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Gun Overlapping"));
	SetIsOverlapping(true);
}

void ABTBGun::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Gun Overlap end"));
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