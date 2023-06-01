// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBEnemyCharacter.h"

#include "BackToBack/Actors/BTBEnemySpawner.h"
#include "BackToBack/Actors/BTBPooledObject.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/WorldPSCPool.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

void ABTBEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBEnemyCharacter::OnWeaponHit);
}

void ABTBEnemyCharacter::Die()
{
	GetMesh()->SetSimulatePhysics(true);
	//SetActorEnableCollision(ECollisionEnabled::);
	UGameplayStatics::PlaySound2D(GetWorld(), sound, 1, 2, 1);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathEffect, GetTransform().GetLocation(), GetTransform().Rotator(), GetTransform().GetScale3D(), true, true, ENCPoolMethod::AutoRelease, true);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimeHandle, this, &ABTBEnemyCharacter::DestroyEnemy, 2, false);
	OnEnemyDeath.Broadcast();
}

void ABTBEnemyCharacter::Damage()
{
	Health--;
	if(Health <= 0)
	{
		Die();
	}
}

void ABTBEnemyCharacter::DestroyEnemy()
{
	GetMesh()->SetSimulatePhysics(false);
	if (Destroy())
	{
		const auto EnemySpawner =
			Cast<ABTBEnemySpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), ABTBEnemySpawner::StaticClass()));

		EnemySpawner->EnemiesArray.Remove(this);
		UE_LOG(LogTemp, Warning, TEXT("Enemy is Destroyed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy is not destroyed"));
	}
}

void ABTBEnemyCharacter::OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABTBPooledObject* Bullet = Cast<ABTBPooledObject>(OtherActor))
	{
		Bullet->DeactivatePooledObject();
		UE_LOG(LogTemp, Warning, TEXT("Bullet hit the enemy"));
		Damage();
	}
}
