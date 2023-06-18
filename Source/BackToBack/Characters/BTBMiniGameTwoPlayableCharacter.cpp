// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameTwoPlayableCharacter.h"

#include "BTBEnemyCharacter.h"
#include "BTBMiniGameOnePlayableCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "BackToBack/HUD/BTBGameHUD.h"
#include "BackToBack/Actors/BTBSpear.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ABTBMiniGameTwoPlayableCharacter::ABTBMiniGameTwoPlayableCharacter()
{
	MilesAnimInstance = GetMesh()->GetAnimInstance();
	
	/*SpearRetrievalPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spear Retrieval Point"));
	SpearRetrievalPoint->SetupAttachment(GetRootComponent());*/
	//DashMeter = FMath::Clamp(DashMeter, 0.0f,1.f);

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SpearPathSpline"));
	SplineComp->SetupAttachment(GetRootComponent());

	SplineEndSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SplineEndSphere"));
	SplineEndSphere->SetupAttachment(SplineComp);

	PlayerSpearVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Spear Summon VFX"));
	PlayerSpearVFX->SetupAttachment(GetRootComponent());
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
		},0.2, false);
	}
}

void ABTBMiniGameTwoPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameTwoPlayableCharacter::OnEnemyHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameTwoPlayableCharacter::OnActorHit);
	
	if (SummonEaseCurve)
	{
		FOnTimelineFloat SummonProgress;
		SummonProgress.BindUFunction(this, FName("SummonUpdate"));
		FOnTimelineEvent SummonFinished;
		SummonFinished.BindUFunction(this, FName("SummonFinished"));

		SummonTimeline.AddInterpFloat(SummonEaseCurve, SummonProgress);
		SummonTimeline.SetTimelineFinishedFunc(SummonFinished);
		//SummonTimeline.PlayFromStart();
	}

}

void ABTBMiniGameTwoPlayableCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// UE_LOG(LogTemp, Warning, TEXT("BTBMiniGameTwoPlayableCharacter Log: %s HP = %d"), *GetName(), Health);
	SummonTimeline.TickTimeline(DeltaSeconds);
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

void ABTBMiniGameTwoPlayableCharacter::OnActorHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABTBSpear>(OtherActor))
	{
		SpearPtr->ResetSpearPhysics();
		AttachSpearToPlayer();
	}
}

void ABTBMiniGameTwoPlayableCharacter::SummonUpdate(float Alpha)
{
	float Opacity = FMath::Lerp(1, 0, Alpha);
	PlayerSpearVFX->SetVariableVec3(FName("FadeVector"), FVector(Opacity, 1.0f, 1.0f));
}

void ABTBMiniGameTwoPlayableCharacter::SummonFinished()
{
	PlayerSpearVFX->SetAsset(nullptr, false);
	//SummonStop();
}

void ABTBMiniGameTwoPlayableCharacter::SummonStart()
{
	SummonTimeline.PlayFromStart();
}

void ABTBMiniGameTwoPlayableCharacter::SummonStop()
{
	SummonTimeline.Reverse();
}

void ABTBMiniGameTwoPlayableCharacter::DrawSpearPath()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!ensure(World != nullptr && SplineStaticMesh != nullptr && SplineMeshMaterial != nullptr))
	{
		return;
	}

	FPredictProjectilePathParams PathParams;
	FPredictProjectilePathResult PathResult;

	PathParams.StartLocation = SplineComp->GetComponentLocation();
	PathParams.LaunchVelocity = GetActorForwardVector() * 1000;
	PathParams.MaxSimTime = 3.0f;
	PathParams.SimFrequency = 20.0f;
	PathParams.DrawDebugTime = 3.0f;
	PathParams.DrawDebugType = EDrawDebugTrace::None;
	PathParams.TraceChannel = ECC_Visibility;
	PathParams.OverrideGravityZ = -1;
	PathParams.ActorsToIgnore.Add(this);
	UGameplayStatics::PredictProjectilePath(World, PathParams, PathResult);

	SplineComp->ClearSplinePoints();
	SplineMeshComponents.Empty();

	for (auto Point : PathResult.PathData)
	{
		SplineComp->AddSplinePoint(Point.Location, ESplineCoordinateSpace::Local);
	}

	const int32 LastIndex = PathResult.PathData.Num() - 1;
	SplineComp->SetSplinePointType(LastIndex, ESplinePointType::CurveClamped);
	
	const FVector LastPointLocation = PathResult.PathData[LastIndex].Location;
	SplineEndSphere->SetWorldLocation(LastPointLocation);

	SpawnMeshesBetweenSplinePoints();
}

void ABTBMiniGameTwoPlayableCharacter::SpawnMeshesBetweenSplinePoints()
{
	for (int i = 0; i < SplineComp->GetNumberOfSplinePoints() - 2; i++)
	{
		USplineMeshComponent* SplineMeshComp =
			NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

		SplineMeshComponents.AddUnique(SplineMeshComp);

		SplineMeshComp->SetStaticMesh(SplineStaticMesh);
		SplineMeshComp->SetMaterial(0, SplineMeshMaterial);
		
		SplineMeshComp->SetMobility(EComponentMobility::Movable);

		FVector CurrentPointLocation, CurrentPointTangent;
		SplineComp->GetLocationAndTangentAtSplinePoint(i, CurrentPointLocation, CurrentPointTangent,
													   ESplineCoordinateSpace::Local);

		FVector NextPointLocation, NextPointTangent;
		SplineComp->GetLocationAndTangentAtSplinePoint(i + 1, NextPointLocation, NextPointTangent,
													   ESplineCoordinateSpace::Local);

		SplineMeshComp->SetStartAndEnd(CurrentPointLocation, CurrentPointTangent,
									   NextPointLocation, NextPointTangent);
	}
	
	RegisterAllComponents();
}

void ABTBMiniGameTwoPlayableCharacter::RemoveSpearPathMeshes()
{
	for (const auto& SplineMesh : SplineMeshComponents)
	{
		SplineMesh->DestroyComponent();
	}
}

void ABTBMiniGameTwoPlayableCharacter::Throw()
{
	bIsThrowing = true;
	bIsSummoning = false;
	bIsAttacking = false;

	DrawSpearPath();
	// RemoveSpearPathMeshes();
	GetSpear()->SetPointLightColorAndIntensity(SpearThrownColor, 350.f);
	//SummonStop();
}

void ABTBMiniGameTwoPlayableCharacter::Summon()
{
	bIsSummoning = true;
	bIsThrowing = false;
	bIsAttacking = false;
	SpearPtr->Summon(this);
	PlayerSpearVFX->SetAsset(SpearSummonVFX, false);
	GetSpear()->SetPointLightColorAndIntensity(SpearSummonColor, 350.f);
	//SummonStop();
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
		SummonStart();
		bIsThrowing = false;
	}
	
}
