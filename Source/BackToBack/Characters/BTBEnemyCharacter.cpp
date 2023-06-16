// Copyright di-tri studio, Inc. All Rights Reserved.

#include "BTBEnemyCharacter.h"

#include "BackToBack/Actors/BTBEnemySpawner.h"
#include "BackToBack/Actors/BTBPooledObject.h"
#include "BackToBack/Actors/BTBSpear.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BackToBack/HUD/BTBEnemyHealthBarHUD.h"
#include "Components/WidgetComponent.h"


ABTBEnemyCharacter::ABTBEnemyCharacter()
{
	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar Widget Comp"));
	HealthWidgetComp->SetupAttachment(GetRootComponent());
}

void ABTBEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBEnemyCharacter::OnWeaponHit);
	
	// ClothMat = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	// BodyMat = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), this);

	Health = MaxHealth;
}

void ABTBEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("BTBEnemyCharacter Log: %s HP = %d"), *GetName(), Health);
}

void ABTBEnemyCharacter::Die()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!ensure(World != nullptr && DeathSound != nullptr && DeathEffect != nullptr))
	{
		return;
	}

	OnAIDeath.Broadcast();

	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	UGameplayStatics::PlaySound2D(World, DeathSound, 1, 2, 1);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		World, DeathEffect, GetTransform().GetLocation(),
		GetTransform().Rotator(), GetTransform().GetScale3D(), true, true,
		ENCPoolMethod::AutoRelease, true);
	
	// ClothMat->SetScalarParameterValue(TEXT("rad"), 20);
	// BodyMat->SetScalarParameterValue(TEXT("rad"), 20);
	//
	// GetMesh()->SetMaterial(0, ClothMat);
	// GetMesh()->SetMaterial(1, BodyMat);

	GetWorldTimerManager().SetTimer(DestroyTimeHandle, this, &ABTBEnemyCharacter::DestroyEnemy, 3, false);
}
void ABTBEnemyCharacter::GetDamaged() 
{
	if (!ensure(DamageEffect != nullptr))
	{
		return;
	}
	
	Health--;
	bIsgettingDamaged = true;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(
		this,
		DamageEffect,
		GetTransform().GetLocation(),
		GetTransform().Rotator(),
		GetTransform().GetScale3D(),
		true,
		true,
		ENCPoolMethod::AutoRelease,
		true
	);
	
	if (Health <= 0)
	{
		Die();
	}
}

void ABTBEnemyCharacter::DestroyEnemy()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!ensure(World != nullptr))
	{
		return;
	}

	GetMesh()->SetSimulatePhysics(false);
	if (IsValid(this))
	{
		const TObjectPtr<ABTBEnemySpawner> EnemySpawner =
			Cast<ABTBEnemySpawner>(UGameplayStatics::GetActorOfClass(World, ABTBEnemySpawner::StaticClass()));

		EnemySpawner->EnemiesArray.Remove(this);
		Destroy();
	}
}

void ABTBEnemyCharacter::OnWeaponHit(UPrimitiveComponent *OverlappedComponent,AActor *OtherActor,UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult &SweepResult) 
{
	if (ABTBPooledObject *Bullet = Cast<ABTBPooledObject>(OtherActor)) 
	{
		Bullet->DeactivatePooledObject();
		GetDamaged();
	}
	
	if (ABTBSpear* Spear = Cast<ABTBSpear>(OtherActor))
	{
		if (Cast<UBoxComponent>(OtherComp))
		{
			GetDamaged();
		}
	}
}

bool ABTBEnemyCharacter::GetGettingDamaged() //added by Jo
{
	return bIsgettingDamaged;
}

void ABTBEnemyCharacter::SetGettingDamaged(bool value) //Added by Jo
{
	bIsgettingDamaged = value;
}

float ABTBEnemyCharacter::CalculateHealthPercentage() const
{
	return Health / MaxHealth;
}
