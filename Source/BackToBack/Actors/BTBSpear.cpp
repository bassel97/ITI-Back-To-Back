// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBSpear.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BackToBack/Characters/BTBEnemyCharacter.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"

ABTBSpear::ABTBSpear()
{
	SpearMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spear Mesh"));
	SpearMesh->SetupAttachment(SceneComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(SceneComponent);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace BoxTraceStart"));
	BoxTraceStart->SetupAttachment(SpearMesh);

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(SpearMesh);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	AddOwnedComponent(ProjectileMovementComponent);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->Velocity = FVector().Zero();
	ProjectileMovementComponent->SetUpdatedComponent(SpearMesh);
	/*ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->InitialSpeed = 150.f;
	ProjectileMovementComponent->MaxSpeed = 200.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingAccelerationMagnitude = 200.f;*/

	EnemySphereDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Sphere Detection"));
	EnemySphereDetection->SetupAttachment(GetRootComponent());
	EnemySphereDetection->SetSphereRadius(50.f, false);
}

void ABTBSpear::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABTBSpear::OnBoxOverlap);
	ActivateBoxCollision();
}

void ABTBSpear::Tick(float DeltaTime)
{
}

void ABTBSpear::ActivateBoxCollision()
{
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABTBSpear::DeactivateBoxCollision()
{
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABTBSpear::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* Pawn = Cast<APawn>(OtherActor))
	{
		if (ABTBMiniGameTwoPlayableCharacter* Player = Cast<ABTBMiniGameTwoPlayableCharacter>(OtherActor))
		{
			if (Player->GetbStartSummoning())
			{
				Player->AttachSpearToPlayer();
				StopSpearBounce();
			}
		}
		else if (ABTBEnemyCharacter* Enemy = Cast<ABTBEnemyCharacter>(OtherActor))
		{
			if (EnemiesArray.IsEmpty())
			{
				PerformSphereTrace(Enemy->GetActorLocation(), Enemy->GetActorLocation(), EnemySphereDetection->GetScaledSphereRadius());
			}

			for (auto EnemyMember : EnemiesArray)
			{
				if (EnemyMember.Key == Enemy)
				{
					EnemiesArray.RemoveSingle(TPair<AActor*, bool>(Enemy, false));
					EnemiesArray.AddUnique(TPair<AActor*, bool>(Enemy, true));
				}
			}
			for (int32 i = 0; i < EnemiesArray.Num(); i++)
			{
				if (Cast<ABTBMiniGameTwoPlayableCharacter>(EnemiesArray[i].Key))
				{
					EnemiesArray.RemoveSingle(EnemiesArray[i]);
				}
			}
			BounceAtEnemies();
		}
		else
		{
			StopSpearBounce();
		}
	}
}

void ABTBSpear::PerformSphereTrace(const FVector& StartLocation, const FVector& EndLocation, float Radius)
{
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitArray;
	ActorsToIgnore.Add(this);
	bool bTraceWork = UKismetSystemLibrary::SphereTraceMulti(
		GetWorld(),
		StartLocation,
		EndLocation,
		Radius,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		HitArray,
		true,
		FColor::Red,
		FColor::Green,
		10.f
	);
	if (bTraceWork)
	{
		if (!HitArray.IsEmpty())
		{
			for (int32 i = 0; i < HitArray.Num(); i++)
			{
				if (!Cast<ABTBMiniGameTwoPlayableCharacter>(HitArray[i].GetActor()) && Cast<ABTBEnemyCharacter>(HitArray[i].GetActor()))
				{
					EnemiesArray.AddUnique(TPair<AActor*, bool>(HitArray[i].GetActor(), false));
				}
			}
		}
	}
}

void ABTBSpear::BounceAtEnemies()
{
	AActor* TargetEnemy = nullptr;
	bool bBounceFinished = false;
	bool bBounceStarted = false;
	EnemyCounter++;
	for (auto EnemyMember : EnemiesArray)
	{
		if (EnemyMember.Value == false && bBounceStarted == false)
		{
			TargetEnemy = EnemyMember.Key;
		}
		else
		{
			bBounceStarted = true;
			if (EnemyCounter == EnemiesArray.Num())
			{
				bBounceFinished = true;
			}
		}
	}
	if (bBounceFinished)
	{
		StopSpearBounce();
		EnemiesArray.Empty();
		EnemyCounter = 0;
	}
	else
	{
		if (TargetEnemy)
		{
			FVector UD = (TargetEnemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			Throw(UD, 200.f);
		}
	}
}

void ABTBSpear::Throw(const FVector& Direction, const float Speed)
{
	ProjectileMovementComponent->Velocity = Direction * Speed;
	Fall(0.f);
}

void ABTBSpear::StopSpearBounce()
{
	ProjectileMovementComponent->StopMovementImmediately();
	Fall(0.f);
}

void ABTBSpear::Fall(float GravityScale)
{
	ProjectileMovementComponent->ProjectileGravityScale = GravityScale;
}

void ABTBSpear::Summon(const FVector& SummoningLocation)
{
	FVector ReturnVector = (SummoningLocation - GetActorLocation());
	FVector ReturnUnitVector = ReturnVector.GetSafeNormal();

	EnemyCounter = 0;
	EnemiesArray.Empty();
	ProjectileMovementComponent->Velocity = ReturnUnitVector * 1000.f;
}

void ABTBSpear::Retrieve()
{
}
