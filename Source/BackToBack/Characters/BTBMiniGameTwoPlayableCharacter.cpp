// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoPlayableCharacter.h"
#include "BackToBack/Actors/BTBSpear.h"

ABTBMiniGameTwoPlayableCharacter::ABTBMiniGameTwoPlayableCharacter()
{
	MilesAnimInstance = GetMesh()->GetAnimInstance();
	
	SpearRetrievalPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spear Retrieval Point"));
	SpearRetrievalPoint->SetupAttachment(GetRootComponent());
}

void ABTBMiniGameTwoPlayableCharacter::SetSpear(ABTBSpear* Spear)
{
	SpearActor = Spear;
}

ABTBSpear* ABTBMiniGameTwoPlayableCharacter::GetSpear()
{
	return SpearActor;
}


// This is DUMB but its fixing an error IDK why this is happening
// If you remove it, character will spin around its Z axis forever after the first move / "HAHA" <- from Yusef
float ABTBMiniGameTwoPlayableCharacter::GetUserInput_X()
{
	if(UserInput_X > 0.01)	return UserInput_X;
	if(UserInput_X < -0.01)	return UserInput_X;
	return 0;
}

float ABTBMiniGameTwoPlayableCharacter::GetUserInput_Y()
{
	if(UserInput_Y > 0.01)	return UserInput_Y;
	if(UserInput_Y < -0.01)	return UserInput_Y;
	return 0;
}

void ABTBMiniGameTwoPlayableCharacter::Throw()
{
	bIsThrowing = true;
	//SetbStartThrowing(false);
}

void ABTBMiniGameTwoPlayableCharacter::Summon()
{
	bIsSummoning = true;
	//SpearActor->Summon(SpearRetrievalPoint->GetComponentLocation());
	SpearActor->Summon(this);
}

void ABTBMiniGameTwoPlayableCharacter::Attack()
{
	bIsAttacking = true;
}

void ABTBMiniGameTwoPlayableCharacter::AttachSpearToPlayer()
{
	if (!SpearActor->IsAttachedTo(this))
	{
		SpearActor->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			TEXT("RightHandSocket"));
		bIsThrowing = false;
	}
}
