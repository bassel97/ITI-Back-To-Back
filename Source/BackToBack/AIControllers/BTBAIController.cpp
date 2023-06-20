// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBAIController.h"

#include "BackToBack/Characters/BTBEnemyCharacter.h"
#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ABTBAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunTheBehaviourTree();
}

void ABTBAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FillPlayerActorsArrayWithAlivePlayers();
	UpdateBlackboardClosestPlayerVariable();
	
	// if (GetPawn()->GetDistanceTo(ClosestPlayer) < 50)
	// {
	// 	Cast<ABTBEnemyCharacter>(GetPawn())->AttackPlayer();
	// }
	
}

void ABTBAIController::RunTheBehaviourTree()
{
	if(!ensure(AIBehaviorTree != nullptr))
	{
		return;
	}
	
	RunBehaviorTree(AIBehaviorTree);
}

void ABTBAIController::FillPlayerActorsArrayWithAlivePlayers()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	
	UGameplayStatics::GetAllActorsOfClass(World, ABTBPlayableCharacter::StaticClass(), PlayerActors);
}

void ABTBAIController::UpdateBlackboardClosestPlayerVariable()
{
	if(!PlayerActors.IsEmpty())
	{
		ClosestPlayer = GetClosestPlayer();
		GetBlackboardComponent()->SetValueAsObject("PlayerActor", ClosestPlayer);
	}
}

TObjectPtr<AActor> ABTBAIController::GetClosestPlayer()
{
	return PlayerActors.Num() > 1 ?
		GetPawn()->GetDistanceTo(PlayerActors[0]) < GetPawn()->GetDistanceTo(PlayerActors[1]) ?
			PlayerActors[0] : PlayerActors[1]
	: PlayerActors[0];

#pragma region NOT AN EXPLANATION, GET GOOD >_<
	// if(PlayerActors.Num() > 1)
	// {
	// 	if(GetPawn()->GetDistanceTo(PlayerActors[0]) < GetPawn()->GetDistanceTo(PlayerActors[1]))
	// 	{
	// 		return PlayerActors[0];
	// 	}
	// 	return PlayerActors[1];
	// }
	// return PlayerActors[0];
	#pragma endregion 
}
