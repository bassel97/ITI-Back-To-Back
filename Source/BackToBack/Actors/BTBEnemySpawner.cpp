// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBEnemySpawner.h"

#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBEnemyCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"


ABTBEnemySpawner::ABTBEnemySpawner()
{
	// SetActorTickEnabled(true);
	// PrimaryActorTick.bCanEverTick = true;
}

void ABTBEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	
	UpdateSpawnEnemyEvery();
	
	World->GetTimerManager().SetTimer
	(
		UpdateEnemySpawnHandle,
		this,
		&ABTBEnemySpawner::UpdateSpawnEnemyEvery,
		0.01f,
		true
	);

	World->GetTimerManager().SetTimer
	(
		EnemySpawnHandle,
		this,
		&ABTBEnemySpawner::SpawnAICharacterAtRandomLocationRelativeToPlayers,
		SpawnEnemyEvery,
		true
	);

	World->GetTimerManager().SetTimer
	(
		UpdateClosestEnemyToPlayersHandle,
		this,
		&ABTBEnemySpawner::UpdateClosestEnemyToPlayers,
		0.025,
		true
	);

	
}

void ABTBEnemySpawner::Tick(float DeltaSeconds)
{
	// Super::Tick(DeltaSeconds);
}

void ABTBEnemySpawner::SpawnAICharacterAtRandomLocationRelativeToPlayers()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}

	if(!ensure(EnemyAIClass != nullptr))
	{
		return;
	}
	
	const FVector RandomLocation = GetARandomLocationInPlayersRange();
	const TObjectPtr<ABTBAICharacter> SpawnedEnemyAI = World->SpawnActor<ABTBAICharacter>(EnemyAIClass, RandomLocation, FRotator::ZeroRotator);
	if(SpawnedEnemyAI)
	{
		EnemiesArray.AddUnique(SpawnedEnemyAI);
	}
	
#if UE_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("SpawnEnemyEvery = %f"), SpawnEnemyEvery);
	UE_LOG(LogTemp, Warning, TEXT("Just spawned an Enemy"));
#endif
}

FVector ABTBEnemySpawner::GetARandomLocationInPlayersRange()
{
	const double RandomX = FMath::FRandRange(Center.X - OuterRange,Center.X + OuterRange);
	const double RandomY = FMath::FRandRange(Center.Y - OuterRange,Center.Y + OuterRange);

	FVector RandLoc = FVector(RandomX, RandomY, 500);
	double Distance = FVector::Distance(Center, RandLoc);

	while (Distance < DistanceFromCenterOfDonutToInnerRange)
	{
		RandLoc = GetARandomLocationInPlayersRange();
		Distance = FVector::Distance(Center, RandLoc);
	}
	
	return RandLoc;
}

void ABTBEnemySpawner::UpdateSpawnEnemyEvery()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	
	SpawnEnemyEvery = SpawnRateCurveClass->GetFloatValue(UGameplayStatics::GetRealTimeSeconds(World));
}

void ABTBEnemySpawner::UpdateClosestEnemyToPlayers()
{
	if(!EnemiesArray.IsEmpty())
	{
		TArray<TPair<ABTBAICharacter*, float>> AICharacterDistancePairs;
		for (const auto Enemy : EnemiesArray)
		{
			const auto EnemyLoc = Enemy->GetActorLocation();
			const auto DistanceToCenterOfPlayers = FVector::DistSquared(EnemyLoc, Center);
			AICharacterDistancePairs.Add(TPair<ABTBAICharacter*, float>(Enemy, DistanceToCenterOfPlayers));
		}
		
		AICharacterDistancePairs.Sort(
			[](const TPair<ABTBAICharacter*, float>& A, const TPair<ABTBAICharacter*, float>& B)
			{
				return A.Value < B.Value;
			}
		);

		ClosestEnemyToPlayers = AICharacterDistancePairs[0].Key;
	}
	
}

ABTBAICharacter* ABTBEnemySpawner::GetClosestEnemyToPlayers()
{
	return ClosestEnemyToPlayers;
}
