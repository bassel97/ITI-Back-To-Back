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
	//SpearMesh->SetupAttachment(SceneComponent);
	RootComponent = SpearMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->AttachToComponent(SpearMesh, FAttachmentTransformRules::KeepRelativeTransform);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace BoxTraceStart"));
	BoxTraceStart->SetupAttachment(SpearMesh);

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(SpearMesh);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	AddOwnedComponent(ProjectileMovementComponent);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->Velocity = FVector().Zero();
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;

	/*ProjectileMovementComponent->InitialSpeed = 150.f;
	ProjectileMovementComponent->MaxSpeed = 200.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingAccelerationMagnitude = 200.f;*/

	EnemySphereDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Sphere Detection"));
	EnemySphereDetection->SetupAttachment(RootComponent);
	EnemySphereDetection->SetSphereRadius(80.f, false);
}

void ABTBSpear::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABTBSpear::OnBoxOverlap);
	DeactivateBoxCollision();
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
			if (Player->bIsSummoning)
			{
				StopSpearBounce(Player);
				DeactivateBoxCollision();
			}
			if (IsAttachedTo(Player))
			{
				bIsAttached = true;
			}
			else
			{
				bIsAttached = false;
			}
		}
		else if (ABTBEnemyCharacter* Enemy = Cast<ABTBEnemyCharacter>(OtherActor))
		{
			if (EnemiesArray.IsEmpty() && !bIsAttached)
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
			StopSpearBounce(OtherActor);
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
	for (auto& EnemyMember : EnemiesArray)
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
		StopSpearBounce(TargetEnemy);
		EnemiesArray.Empty();
		EnemyCounter = 0;
		//HomingFunction(false, 0.f, 0.f, 0.f, nullptr);
	}
	else
	{
		if (TargetEnemy)
		{
			FVector UD = (TargetEnemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			//HomingFunction(true, 150.f, 200.f, 300.f, TargetEnemy);
			Throw(UD, 500.f);
		}
	}
}

void ABTBSpear::Throw(const FVector& Direction, const float Speed)
{
	bIsAttached = false;
	ProjectileMovementComponent->Velocity = Direction * Speed;
}


void ABTBSpear::StopSpearBounce(AActor* SpearNewParentActor)
{
	if (ABTBMiniGameTwoPlayableCharacter* Player = Cast<ABTBMiniGameTwoPlayableCharacter>(SpearNewParentActor))
	{
		ProjectileMovementComponent->StopMovementImmediately();
		Player->AttachSpearToPlayer();
		bIsAttached = true;
		Fall(0.f);
	}
	//else if (ABTBEnemyCharacter* Enemy = Cast<ABTBEnemyCharacter>(SpearNewParentActor))
	//{
	//	/*ProjectileMovementComponent->StopMovementImmediately();
	//	AttachToComponent(Enemy->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	//	DeactivateBoxCollision();*/
	//	//ProjectileMovementComponent->StopMovementImmediately();
	//	Fall(0.05f);
	//}
	else
	{
		//ProjectileMovementComponent->StopMovementImmediately();
		Fall(0.05f);
	}
}


void ABTBSpear::Fall(float GravityScale)
{
	ProjectileMovementComponent->ProjectileGravityScale = GravityScale;
}

void ABTBSpear::Summon(AActor* SummoningLocation)
{
	FVector ReturnVector = (SummoningLocation->GetActorLocation() - GetActorLocation());
	FVector ReturnUnitVector = ReturnVector.GetSafeNormal();

	EnemyCounter = 0;
	EnemiesArray.Empty();
	ActivateBoxCollision();
	//HomingFunction(false, 0.f, 0.f, 0.f, nullptr);
	//ProjectileMovementComponent->Velocity = ReturnUnitVector * 1000.f;
	Fall(0.f);
	Throw(ReturnUnitVector, 1000.f);
}

void ABTBSpear::Retrieve()
{
}




void ABTBSpear::HomingFunction(bool bIsHoming, float InitialSpeed, float MaxSpeed, float HomingAcceleration, AActor* Target)
{
	ProjectileMovementComponent->bIsHomingProjectile = bIsHoming;
	ProjectileMovementComponent->InitialSpeed = InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	if (Target)
	{
		ProjectileMovementComponent->HomingTargetComponent = Target->GetRootComponent();
	}
}