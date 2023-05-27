// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBEnemySpawner.h"

#include "BackToBack/Characters/BTBAICharacter.h"
#include "BackToBack/Characters/BTBEnemyCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"

ABTBEnemySpawner::ABTBEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
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
}

// void ABTBEnemySpawner::Tick(float DeltaSeconds)
// {
// 	Super::Tick(DeltaSeconds);
// 	const TObjectPtr<UWorld> World = GetWorld();
// 	if(!ensure(World != nullptr))
// 	{
// 		return;
// 	}
//
// 	
// 	//const FVector PlayersMidPoint = Center /*GetPlayersMidPoint()*/ ;
// 	
// 	//if(!EnemySpawnHandle.IsValid())
// 	//{
// 	//	World->GetTimerManager().SetTimer
// 	//	(
// 	//		EnemySpawnHandle,
// 	//		this,
// 	//		&ABTBEnemySpawner::SpawnAICharacterAtRandomLocationRelativeToPlayers,
// 	//		SpawnEnemyEvery /*SpawnRateCurveClass->GetFloatValue(UGameplayStatics::GetRealTimeSeconds(GetWorld()))*/,
// 	//		false
// 	//	);
// 	//}
// 	
// }

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
	World->SpawnActor<ABTBAICharacter>(EnemyAIClass, RandomLocation, FRotator::ZeroRotator);
	// GetWorldTimerManager().ClearTimer(EnemySpawnHandle);
	
#if UE_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("SpawnEnemyEvery = %f"), SpawnEnemyEvery);
	UE_LOG(LogTemp, Warning, TEXT("Just spawned an Enemy"));
#endif
}

FVector ABTBEnemySpawner::GetARandomLocationInPlayersRange()
{
	const double RandomX = FMath::FRandRange(Center.X - OuterRange,Center.X + OuterRange);
	const double RandomY = FMath::FRandRange(Center.Y - OuterRange,Center.Y + OuterRange);

	FVector RandLoc = FVector(RandomX, RandomY, 1125);
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
