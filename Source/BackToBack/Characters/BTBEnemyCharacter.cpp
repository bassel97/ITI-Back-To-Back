// Copyright di-tri studio, Inc. All Rights Reserved.

#include "BTBEnemyCharacter.h"

#include "BackToBack/Actors/BTBEnemySpawner.h"
#include "BackToBack/Actors/BTBPooledObject.h"
#include "BackToBack/Actors/BTBSpear.h"
#include "BackToBack/HUD/BTBEnemyHealthBarHUD.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ABTBEnemyCharacter::ABTBEnemyCharacter() {
  HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar Widget Comp"));
  HealthWidgetComp->SetupAttachment(GetRootComponent());

  CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
  CollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightHandSocket");
  CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  
  SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
  SphereCollision->SetupAttachment(GetRootComponent());
  
}

void ABTBEnemyCharacter::BeginPlay() {
  Super::BeginPlay();
  GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBEnemyCharacter::OnWeaponHit);

  SphereCollision->OnComponentBeginOverlap.AddDynamic(this,&ABTBEnemyCharacter::OnPlayerGetCloser);
  Health = MaxHealth;
}


void ABTBEnemyCharacter::Tick(float DeltaSeconds) {
  Super::Tick(DeltaSeconds);
}

void ABTBEnemyCharacter::AttackPlayer()
{
  SetIsAttackingPlayer(true);
}
void ABTBEnemyCharacter::Die() {
  const TObjectPtr<UWorld> World = GetWorld();
  if (!ensure(World != nullptr && DeathSound != nullptr &&
              DeathEffect != nullptr)) {
    return;
  }

  OnAIDeath.Broadcast();

  GetMesh()->SetSimulatePhysics(true);
  GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
  GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

  UGameplayStatics::PlaySound2D(World, DeathSound, .2, 1, 1);

  UNiagaraFunctionLibrary::SpawnSystemAtLocation(
      World, DeathEffect, GetTransform().GetLocation(),
      GetTransform().Rotator(), GetTransform().GetScale3D(), true, true,
      ENCPoolMethod::AutoRelease, true);
  GetWorldTimerManager().SetTimer(DestroyTimeHandle, this,
                                  &ABTBEnemyCharacter::DestroyEnemy, 3, false);
}
void ABTBEnemyCharacter::GetDamaged() {
  if (!ensure(DamageEffect != nullptr)) {
    return;
  }

  Health--;
  bIsgettingDamaged = true;

  UNiagaraFunctionLibrary::SpawnSystemAtLocation(
      this, DamageEffect, GetTransform().GetLocation(),
      GetTransform().Rotator(), GetTransform().GetScale3D(), true, true,
      ENCPoolMethod::AutoRelease, true);

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

void ABTBEnemyCharacter::OnWeaponHit(UPrimitiveComponent *OverlappedComponent,
                                     AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp,
                                     int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult &SweepResult) {
  if (ABTBPooledObject *Bullet = Cast<ABTBPooledObject>(OtherActor)) {
    Bullet->DeactivatePooledObject();
    GetDamaged();
  }

  if (ABTBSpear *Spear = Cast<ABTBSpear>(OtherActor)) {
    if (Cast<UBoxComponent>(OtherComp)) {
      GetDamaged();
    }
  }
}

void ABTBEnemyCharacter::OnPlayerGetCloser(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (Cast<ABTBMiniGameTwoPlayableCharacter>(OtherActor))
  {
    AttackPlayer();
  }
}

bool ABTBEnemyCharacter::GetGettingDamaged()
{
  return bIsgettingDamaged;
}

void ABTBEnemyCharacter::SetGettingDamaged(bool value) 
{
  bIsgettingDamaged = value;
}

float ABTBEnemyCharacter::CalculateHealthPercentage() const {
  return Health / MaxHealth;
}
