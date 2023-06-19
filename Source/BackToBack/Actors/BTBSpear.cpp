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
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement Component"));
	AddOwnedComponent(RotatingMovementComponent);
	RotatingMovementComponent->RotationRate = FRotator(0.f, 0.f, 0.f);
	RotatingMovementComponent->PivotTranslation = FVector(0.f, 0.f, 0.f);

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
	TArray<AActor*> IgnoreActorsArray;
	IgnoreActorsArray.Add(this);
	FHitResult HitRes;
	UKismetSystemLibrary::BoxTraceSingle(
		GetWorld(),
		BoxTraceStart->GetComponentLocation(),
		BoxTraceEnd->GetComponentLocation(),
		CollisionBox->GetScaledBoxExtent() / 2.f,
		BoxTraceEnd->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		IgnoreActorsArray,
		EDrawDebugTrace::ForDuration,
		HitRes,
		false,
		FColor::Red,
		FColor::Green,
		4.f
	);
	if (HitRes.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("the actor is: %s"), *HitRes.GetActor()->GetName());
		if (!Cast<APawn>(HitRes.GetActor()))
		{
			StopSpearBounce(HitRes.GetActor());
		}
	}
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
	if (bIsSummoning)
	{
		ProjectileMovementComponent->bRotationFollowsVelocity = false;
		RotatingMovementComponent->RotationRate = FRotator(0.f, 1500.f, 0.f);
		Fall(0.f);
	}
	else
	{
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		RotatingMovementComponent->RotationRate = FRotator(0.f, 0.f, 0.f);
		Fall(ThrowGravityScale);
	}
	bIsAttached = false;
	ProjectileMovementComponent->Velocity = Direction * Speed;
	SpearVFX->SetAsset(SpearThrowVFX, false);
	
}


void ABTBSpear::StopSpearBounce(AActor* HitActor)
{
	if (ABTBMiniGameTwoPlayableCharacter* Player = Cast<ABTBMiniGameTwoPlayableCharacter>(HitActor))
	{
		Player->AttachSpearToPlayer();
		ResetSpearPhysics();
		SpearVFX->SetAsset(nullptr, false);
		Fall(0.f);
		SetPointLightColorAndIntensity(SpearInHandColor, 200.f);
	}
	else
	{
		if (HitActor != nullptr)
		{
			if (!bIsSummoning)
			{
				ProjectileMovementComponent->StopMovementImmediately();
				bIsAttached = false;
				DeactivateBoxCollision();
				Fall(0.f);
			}
		}
		else
		{
			bIsAttached = false;
			Fall(2.f);
		}
	}
}

void ABTBSpear::ResetSpearPhysics()
{
	ProjectileMovementComponent->StopMovementImmediately();
	RotatingMovementComponent->RotationRate = FRotator().ZeroRotator;
	bIsAttached = true;
	bIsSummoning = false;
}

void ABTBSpear::Fall(float GravityScale)
{
	ProjectileMovementComponent->ProjectileGravityScale = GravityScale;
}

void ABTBSpear::Summon(AActor* SummoningLocation)
{
	bIsSummoning = true;
	FVector ReturnVector = (SummoningLocation->GetActorLocation() - GetActorLocation());
	FVector ReturnUnitVector = ReturnVector.GetSafeNormal();
	EnemiesArray.Empty();
	ActivateBoxCollision();
	Throw(ReturnUnitVector, SpearSpeed);
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