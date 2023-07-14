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


float ABTBMiniGameOnePlayableCharacter::GetUserInput_X()
{
	if(bIsSingleMode)
	{
		if(OtherPlayer)
		{
			OtherPlayer->SetUserInput_X(this->UserInput_X);
		}
		return this->UserInput_X;
	}
	else
	{
		if (UserInput_X >= 0.925f && OtherPlayer->UserInput_X >= 0.925f)		return 1;
		if (UserInput_X <= -0.975f && OtherPlayer->UserInput_X <= -0.975f)		return -1;
		return 0;
	}
}

void ABTBMiniGameOnePlayableCharacter::Die()
{
	Super::Die();
	
	UE_LOG(LogTemp, Warning, TEXT("Minigame one player died"));
}

void ABTBMiniGameOnePlayableCharacter::OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ABTBEnemyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy is casted successfully"));
		OtherActor->SetActorEnableCollision(ECollisionEnabled::NoCollision);
		Die();
	}
}

void ABTBMiniGameOnePlayableCharacter::SetAndResetLeftButtonEnum(const bool bIsSet)
{
	bIsSet ?
		LeftButtonState = ELeftButtonStates::SwitchGun :
	LeftButtonState = ELeftButtonStates::None;
}

void ABTBMiniGameOnePlayableCharacter::SetAndResetRightTriggerEnum(const bool bIsSet)
{
	bIsSet ?
		RightTriggerButtonState = ERightTriggerButtonStates::Shoot :
	RightTriggerButtonState = ERightTriggerButtonStates::None;
}

void ABTBMiniGameOnePlayableCharacter::SetAndResetLeftTriggerEnum(const bool bIsSet)
{
	//TODO: Uncomment and Edit that later if the button is needed in mini game one
	// bIsSet ?
	// 	LeftTriggerButtonState = ELeftTriggerButtonStates::None :
	// LeftTriggerButtonState = ELeftTriggerButtonStates::None;
	LeftTriggerButtonState = ELeftTriggerButtonStates::None;
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
