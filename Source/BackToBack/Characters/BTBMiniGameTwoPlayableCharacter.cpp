// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoPlayableCharacter.h"

#include "BTBEnemyCharacter.h"
#include "BTBMiniGameOnePlayableCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "BackToBack/HUD/BTBGameHUD.h"
#include "BackToBack/Actors/BTBSpear.h"
#include "Components/CapsuleComponent.h"

ABTBMiniGameTwoPlayableCharacter::ABTBMiniGameTwoPlayableCharacter()
{
	MilesAnimInstance = GetMesh()->GetAnimInstance();
	
	SpearRetrievalPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spear Retrieval Point"));
	SpearRetrievalPoint->SetupAttachment(GetRootComponent());
	//DashMeter = FMath::Clamp(DashMeter, 0.0f,1.f);
	
}

void ABTBMiniGameTwoPlayableCharacter::Dash()
{
	DashMeter -= 0.2f;
	if (!(DashMeter < 0) )
	{
		UE_LOG(LogTemp,Warning,TEXT("Honga bonga"))
		LaunchCharacter(GetActorForwardVector()*3500,false,false);
		SetbIsDashing(true);
		//float whtIsDashMeterNow = DashMeter;
		
		
		PlayerDash.Broadcast(DashMeter);
		
		GetMesh()->GetChildComponent(0)->SetActive(true,true);
		
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			GetMesh()->GetChildComponent(0)->SetActive(false,false);
		}, 0.2, false);
	}
}

void ABTBMiniGameTwoPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameTwoPlayableCharacter::OnEnemyHit);
}

void ABTBMiniGameTwoPlayableCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// UE_LOG(LogTemp, Warning, TEXT("BTBMiniGameTwoPlayableCharacter Log: %s HP = %d"), *GetName(), Health);
}

void ABTBMiniGameTwoPlayableCharacter::SetSpear(ABTBSpear* Spear)
{
	SpearPtr = Spear;
}

ABTBSpear* ABTBMiniGameTwoPlayableCharacter::GetSpear()
{
	return SpearPtr;
}

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
