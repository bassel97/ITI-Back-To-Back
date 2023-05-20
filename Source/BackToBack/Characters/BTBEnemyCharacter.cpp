// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBEnemyCharacter.h"
#include "BackToBack/Actors/BTBPooledObject.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


void ABTBEnemyCharacter::Die()
{
	GetMesh()->PlayAnimation(DeathAnimation, false);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimeHandle, this, &ABTBEnemyCharacter::DestroyEnemy, DeathAnimation->GetPlayLength(), false);
}

void ABTBEnemyCharacter::BeginPlay()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBEnemyCharacter::OnWeaponHit);
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
	/*if (Destroy())
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy is Destroyed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy is not destroyed"));
	}*/
	SetActorHiddenInGame(true);
}

void ABTBEnemyCharacter::OnWeaponHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABTBPooledObject* bullet = Cast<ABTBPooledObject>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet hit the enemy"));
		Damage();
	}
}
