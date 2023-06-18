// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBSpear.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BackToBack/Characters/BTBEnemyCharacter.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"

ABTBSpear::ABTBSpear()
{
	SpearMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spear Mesh"));
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
	
	/*EnemySphereDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Sphere Detection"));
	EnemySphereDetection->SetupAttachment(RootComponent);
	EnemySphereDetection->SetSphereRadius(80.f, false);*/
	SpearSpeed = 1000.0f;
	SpearVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Spear VFX Component"));
	SpearVFX->SetupAttachment(SpearMesh);

	SpearPointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Spear Point Light Component"));
	SpearPointLight->SetupAttachment(SpearMesh);
}

void ABTBSpear::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABTBSpear::OnBoxOverlap);
	DeactivateBoxCollision();
	SetPointLightColorAndIntensity(SpearInHandColor, 200.f);
}

void ABTBSpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTBSpear::ActivateBoxCollision()
{
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABTBSpear::DeactivateBoxCollision()
{
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABTBSpear::SetPointLightColorAndIntensity(FLinearColor Color, float Intensity)
{
	SpearPointLight->SetLightColor(Color);
	SpearPointLight->SetIntensity(Intensity);
}

void ABTBSpear::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<AActor*> SphereActorsToIgnore;
	if (APawn* Pawn = Cast<APawn>(OtherActor))
	{
		if (ABTBMiniGameTwoPlayableCharacter* Player = Cast<ABTBMiniGameTwoPlayableCharacter>(OtherActor))
		{
			SphereActorsToIgnore.Add(Player);
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
			SphereActorsToIgnore.Add(Enemy);
			if (EnemiesArray.IsEmpty() && !bIsAttached)
			{
				PerformSphereTrace(Enemy->GetActorLocation(), Enemy->GetActorLocation(), 800.f, SphereActorsToIgnore);
			}
			TArray<AActor*> EnemiesList;
			int32 EnemiesNum = EnemiesArray.GetKeys(EnemiesList);
			for (int32 i = 0; i < EnemiesNum; i++)
			{
				if (EnemiesList[i] == Enemy)
				{
					EnemiesArray.Emplace(EnemiesList[i], true);
				}
			}
			if (!bIsAttached)
			{
				BounceAtEnemies();
			}
		}
	}
	else
	{
		if (OtherActor != this)
		{
			StopSpearBounce(OtherActor);
		}
	}
}

void ABTBSpear::PerformSphereTrace(const FVector& StartLocation, const FVector& EndLocation, float Radius, TArray<AActor*> SphereActorsToIgnore)
{
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitArray;
	ActorsToIgnore.Add(this);
	for (int32 i = 0; i < SphereActorsToIgnore.Num(); i++)
	{
		ActorsToIgnore.Add(SphereActorsToIgnore[i]);
	}
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
				if (Cast<ABTBEnemyCharacter>(HitArray[i].GetActor()))
				{
					EnemiesArray.Add(HitArray[i].GetActor(), false);
				}
			}
		}
	}
}

void ABTBSpear::BounceAtEnemies()
{
	AActor* TargetEnemy = nullptr;
	bool bBounceStarted = false;
	
	for (auto& EnemyMember : EnemiesArray)
	{
		if (EnemyMember.Value == false && bBounceStarted == false)
		{
			TargetEnemy = EnemyMember.Key;
		}
		else
		{
			bBounceStarted = true;
		}
	}
	if (TargetEnemy)
	{
		FVector UD = (TargetEnemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		//HomingFunction(true, 150.f, 200.f, 300.f, TargetEnemy);
		Throw(UD, SpearSpeed);
	}
	else
	{
		StopSpearBounce(TargetEnemy);
		EnemiesArray.Empty();
	}
}

void ABTBSpear::Throw(const FVector& Direction, const float Speed)
{
	bIsAttached = false;
	ProjectileMovementComponent->Velocity = Direction * Speed;
	SpearVFX->SetAsset(SpearThrowVFX, false);
}


void ABTBSpear::StopSpearBounce(AActor* HitActor)
{
	if (ABTBMiniGameTwoPlayableCharacter* Player = Cast<ABTBMiniGameTwoPlayableCharacter>(HitActor))
	{
		ProjectileMovementComponent->StopMovementImmediately();
		Player->AttachSpearToPlayer();
		bIsAttached = true;
		SpearVFX->SetAsset(nullptr, false);
		//Player->SummonStop();
		Fall(0.f);
		SetPointLightColorAndIntensity(SpearInHandColor, 200.f);
	}
	else
	{
		if (HitActor != nullptr)
		{
			ProjectileMovementComponent->StopMovementImmediately();
			bIsAttached = false;
			DeactivateBoxCollision();
			Fall(0.f);
		}
		else
		{
			bIsAttached = false;
			Fall(1.f);
			
		}
		
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
	Fall(0.f);
	Throw(ReturnUnitVector, SpearSpeed);
	UE_LOG(LogTemp, Warning, TEXT("Summon from the spear class"));
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