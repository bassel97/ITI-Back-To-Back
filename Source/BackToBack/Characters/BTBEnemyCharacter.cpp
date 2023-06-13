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


void ABTBEnemyCharacter::BeginPlay() {
  Super::BeginPlay();
  GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(
      this, &ABTBEnemyCharacter::OnWeaponHit);
}

void ABTBEnemyCharacter::Die() 
{
  const TObjectPtr<UWorld> World = GetWorld();
  if (!ensure(World != nullptr)) {
    return;
  }

  OnAIDeath.Broadcast();

  GetMesh()->SetSimulatePhysics(true);
  GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
  GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

  UGameplayStatics::PlaySound2D(World, sound, 1, 2, 1);

  UNiagaraFunctionLibrary::SpawnSystemAtLocation(
      World, DeathEffect, GetTransform().GetLocation(),
      GetTransform().Rotator(), GetTransform().GetScale3D(), true, true,
      ENCPoolMethod::AutoRelease, true);

  GetWorldTimerManager().SetTimer(DestroyTimeHandle, this,
                                  &ABTBEnemyCharacter::DestroyEnemy, 3, false);
}

void ABTBEnemyCharacter::Damage() 
{
	Health--;

		bIsgettingDamaged = true;
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle,DamageAnimation->GetPlayLength(),false,-1);
	
		// GetMesh()->PlayAnimation(DamageAnimation,false);

	if (ensure(DamageEffect))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DamageEffect, GetTransform().GetLocation(),
	GetTransform().Rotator(), GetTransform().GetScale3D(), true, true,
	ENCPoolMethod::AutoRelease, true);
	}
  if (Health <= 0) {
    Die();
  }
}

void ABTBEnemyCharacter::DestroyEnemy() {
  const TObjectPtr<UWorld> World = GetWorld();
  if (!ensure(World != nullptr)) {
    return;
  }

  GetMesh()->SetSimulatePhysics(false);
  if (IsValid(this)) {
    const TObjectPtr<ABTBEnemySpawner> EnemySpawner =
        Cast<ABTBEnemySpawner>(UGameplayStatics::GetActorOfClass(
            World, ABTBEnemySpawner::StaticClass()));

    EnemySpawner->EnemiesArray.Remove(this);
    Destroy();
  }
}

void ABTBEnemyCharacter::OnWeaponHit(UPrimitiveComponent *OverlappedComponent,AActor *OtherActor,UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult &SweepResult) 
{
  if (ABTBPooledObject *Bullet = Cast<ABTBPooledObject>(OtherActor)) 
  {
      Bullet->DeactivatePooledObject();
      Damage();
  }
  if (ABTBSpear* Spear = Cast<ABTBSpear>(OtherActor))
  {
      if (Cast<UBoxComponent>(OtherComp))
      {
          Damage();
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
