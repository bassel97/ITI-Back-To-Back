// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameOnePlayableCharacter.h"
#include "BTBEnemyCharacter.h"
#include "BackToBack/Actors/BTBGun.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

void ABTBMiniGameOnePlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameOnePlayableCharacter::OnBoxOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABTBMiniGameOnePlayableCharacter::OnBoxEndOverlap);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameOnePlayableCharacter::OnEnemyHit);
}

ABTBMiniGameOnePlayableCharacter::ABTBMiniGameOnePlayableCharacter()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	CollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");

	GunSwitchPosition = CreateDefaultSubobject<UChildActorComponent>(TEXT("GunSwitchPosition"));
	GunSwitchPosition->SetupAttachment(GetMesh());
}


float ABTBMiniGameOnePlayableCharacter::GetRotationValue()
{
	if(RotationValue >= 0.925f && OtherPlayer->RotationValue >= 0.925f)		return 0.75;
	if(RotationValue <= -0.975f && OtherPlayer->RotationValue <= -0.975f)		return -0.75;
	return 0;
}

void ABTBMiniGameOnePlayableCharacter::Die()
{
	Super::Die();
	
	UE_LOG(LogTemp, Warning, TEXT("Minigame one player died"));
}

void ABTBMiniGameOnePlayableCharacter::OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Collision Occured"));
	if(Cast<ABTBEnemyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy is casted successfully"));
		Die();
	}
}

//Switch Action
void ABTBMiniGameOnePlayableCharacter::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABTBMiniGameOnePlayableCharacter>(OtherActor) && OtherActor != nullptr && OtherComp != nullptr && OtherActor != this)
	{
		if (OtherComp->ComponentHasTag("Hand"))
		{
			IsOverlapping = true;
		}
	}
}

void ABTBMiniGameOnePlayableCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsOverlapping = false;
}



//Get and Set GUN
void ABTBMiniGameOnePlayableCharacter::SetGun(ABTBGun* Gun)
{
	GunActor = Gun;
}

ABTBGun* ABTBMiniGameOnePlayableCharacter::GetGun()
{
	return GunActor;
}
