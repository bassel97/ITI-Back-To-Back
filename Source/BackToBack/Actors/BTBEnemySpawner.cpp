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

void ABTBEnemySpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	
	const FVector PlayersMidPoint = Center /*GetPlayersMidPoint()*/ ;
	
	if(!EnemySpawnHandle.IsValid())
	{
		World->GetTimerManager().SetTimer
		(
			EnemySpawnHandle,
			this,
			&ABTBEnemySpawner::SpawnAICharacterAtRandomLocationRelativeToPlayers,
			20 /*SpawnRateCurveClass->GetFloatValue(UGameplayStatics::GetRealTimeSeconds(GetWorld()))*/,
			false
		);
	}
	
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
	World->SpawnActor<ABTBAICharacter>(EnemyAIClass, RandomLocation, FRotator::ZeroRotator);
	GetWorldTimerManager().ClearTimer(EnemySpawnHandle);
}

FVector ABTBEnemySpawner::GetARandomLocationInPlayersRange()
{
	//const FVector Center = GetPlayersMidPoint();
	const double RandomX = FMath::FRandRange(Center.X - OuterRange,Center.X + OuterRange);
	const double RandomY = FMath::FRandRange(Center.Y - OuterRange,Center.Y + OuterRange);

	FVector RandLoc = FVector(RandomX, RandomY, Center.Z);
	double Distance = FVector::Distance(Center, RandLoc);

	while (Distance < DistanceFromCenterOfDonutToInnerRange)
	{
		RandLoc = GetARandomLocationInPlayersRange();
		Distance = FVector::Distance(Center, RandLoc);
	}
	
	return RandLoc;
}