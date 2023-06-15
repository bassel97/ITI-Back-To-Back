// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoPlayableCharacter.h"

#include "BTBEnemyCharacter.h"
#include "BTBMiniGameOnePlayableCharacter.h"
#include "BackToBack/Actors/BTBSpear.h"
#include "Components/CapsuleComponent.h"

ABTBMiniGameTwoPlayableCharacter::ABTBMiniGameTwoPlayableCharacter()
{
	MilesAnimInstance = GetMesh()->GetAnimInstance();
	
	SpearRetrievalPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spear Retrieval Point"));
	SpearRetrievalPoint->SetupAttachment(GetRootComponent());
}

void ABTBMiniGameTwoPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameTwoPlayableCharacter::OnEnemyHit);
}

void ABTBMiniGameTwoPlayableCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UE_LOG(LogTemp, Warning, TEXT("%s HP = %d"), *GetName(), Health);
}

void ABTBMiniGameTwoPlayableCharacter::SetSpear(ABTBSpear* Spear)
{
	SpearPtr = Spear;
}

ABTBSpear* ABTBMiniGameTwoPlayableCharacter::GetSpear()
{
	return SpearPtr;
}


// // This is DUMB but its fixing an error IDK why this is happening
// // If you remove it, character will spin around its Z axis forever after the first move / "HAHA" <- from Yusef
// float ABTBMiniGameTwoPlayableCharacter::GetUserInput_X()
// {
// 	if(UserInput_X > 0.01)	return UserInput_X;
// 	if(UserInput_X < -0.01)	return UserInput_X;
// 	return 0;
// }
//
// float ABTBMiniGameTwoPlayableCharacter::GetUserInput_Y()
// {
// 	if(UserInput_Y > 0.01)	return UserInput_Y;
// 	if(UserInput_Y < -0.01)	return UserInput_Y;
// 	return 0;
// }


void ABTBMiniGameTwoPlayableCharacter::OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsDead) return;

	if (Cast<ABTBEnemyCharacter>(OtherActor))
	{
		Health--;
		if (Health <= 0)
		{
			bIsDead = true;
			Die();
			Destroy();
		}
		// bIsDead = true;
		// Die();
		// Destroy();
	}
}

void ABTBMiniGameTwoPlayableCharacter::Throw()
{
	bIsThrowing = true;
	bIsSummoning = false;
	bIsAttacking = false;
}

void ABTBMiniGameTwoPlayableCharacter::Summon()
{
	bIsSummoning = true;
	bIsThrowing = false;
	bIsAttacking = false;
	SpearPtr->Summon(this);
}

bool ABTBMiniGameTwoPlayableCharacter::GetbIsAttacking()
{
	return bIsAttacking;
}

void ABTBMiniGameTwoPlayableCharacter::SetbIsAttacking(bool Value)
{
	bIsAttacking = Value;
}


void ABTBMiniGameTwoPlayableCharacter::Die()
{
	if(bIsDead == true && OtherPlayer->bIsDead == true)
	{
		Super::Die();

#if UE_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("MG2 Players're DEAD"));
#endif
	}
}

void ABTBMiniGameTwoPlayableCharacter::AttachSpearToPlayer()
{
	if (!SpearPtr->IsAttachedTo(this))
	{
		SpearPtr->AttachToComponent
		(
			GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			TEXT("RightHandSocket")
		);
		
		bIsThrowing = false;
	}
}
