// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBEnemySpawner.h"

#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBEnemyCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"


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
}

void ABTBEnemySpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateClosestEnemyToPlayers();
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
	auto SpawnedEnemyAI = World->SpawnActor<ABTBAICharacter>(EnemyAIClass, RandomLocation, FRotator::ZeroRotator);
	EnemiesArray.Add(SpawnedEnemyAI);
	
#if UE_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("SpawnEnemyEvery = %f"), SpawnEnemyEvery);
	UE_LOG(LogTemp, Warning, TEXT("Just spawned an Enemy"));
#endif
}

FVector ABTBEnemySpawner::GetARandomLocationInPlayersRange()
{
	const double RandomX = FMath::FRandRange(Center.X - OuterRange,Center.X + OuterRange);
	const double RandomY = FMath::FRandRange(Center.Y - OuterRange,Center.Y + OuterRange);

	FVector RandLoc = FVector(RandomX, RandomY, 200);
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
	//TArray<float> Distances;
	//TMap<ABTBAICharacter*, TPair<FVector, float>> ActorMap;
	
	TArray<TPair<ABTBAICharacter*, float>> AICharacterDistancePairs;
	
	for (const auto Enemy : EnemiesArray)
	{
		auto EnemyLoc = Enemy->GetActorLocation();
		auto DistanceToCenterOfPlayers = FVector::DistSquared(EnemyLoc, Center);
		AICharacterDistancePairs.Add(TPair<ABTBAICharacter*, float>(Enemy, DistanceToCenterOfPlayers));
	}

	// Sort the array based on the distance in ascending order
	AICharacterDistancePairs.Sort(
		[](const TPair<ABTBAICharacter*, float>& A, const TPair<ABTBAICharacter*, float>& B)
		{
			return A.Value < B.Value;
		}
	);

	ClosestEnemyToPlayers = AICharacterDistancePairs[0].Key;
	
}

ABTBAICharacter* ABTBEnemySpawner::GetClosestEnemyToPlayers()
{
	return ClosestEnemyToPlayers;
}
