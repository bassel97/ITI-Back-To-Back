// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameOnePlayableCharacter.h"
#include "BTBEnemyCharacter.h"
#include "Components/CapsuleComponent.h"

void ABTBMiniGameOnePlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameOnePlayableCharacter::OnEnemyHit);
}

float ABTBMiniGameOnePlayableCharacter::GetRotationValue()
{
	if(RotationValue >= 0.925f && OtherPlayer->RotationValue >= 0.925f)		return 1;
	if(RotationValue <= -0.975f && OtherPlayer->RotationValue <= -0.975f)		return -1;
	return 0;
}

void ABTBMiniGameOnePlayableCharacter::Die()
{
	Super::Die();
}

void ABTBMiniGameOnePlayableCharacter::OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABTBEnemyCharacter* Enemy = Cast<ABTBEnemyCharacter>(OtherActor))
	{
		Die();
	}
}
