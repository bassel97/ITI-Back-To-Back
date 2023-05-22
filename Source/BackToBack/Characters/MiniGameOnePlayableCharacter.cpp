// Copyright di-tri studio, Inc. All Rights Reserved.


#include "MiniGameOnePlayableCharacter.h"
#include  "BTBEnemyCharacter.h"
#include "Components/CapsuleComponent.h"


void AMiniGameOnePlayableCharacter::Die()
{
	Super::Die();
}


void AMiniGameOnePlayableCharacter::OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABTBEnemyCharacter* enemy = Cast<ABTBEnemyCharacter>(OtherActor))
	{
		Die();
	}

}
float AMiniGameOnePlayableCharacter::GetRotationValue()
{
	if(RotationValue >= 0.925f && OtherPlayer->RotationValue >= 0.925f)	        return 1;
	else if(Super::GetRotationValue() <= -0.925f && OtherPlayer->RotationValue <= -0.925f)	return -1;
	 else return 0;
}

//bool AMiniGameOnePlayableCharacter::GetbStartSwitching()
//{
//	if (bStartSwitching == true && OtherPlayer->bStartSwitching == true) return 1;
//	else return 0;
//	/*return Super::GetbStartSwitching();*/
//}

