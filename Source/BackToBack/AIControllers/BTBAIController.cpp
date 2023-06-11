// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBAIController.h"

#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ABTBAIController::BeginPlay()
{
	Super::BeginPlay();
	
	FillPlayerActorsArray();
	RunTheBehaviourTree();
}

void ABTBAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateBlackboardClosestPlayerVariable();
}

void ABTBAIController::FillPlayerActorsArray()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	
	UGameplayStatics::GetAllActorsOfClass(World, ABTBPlayableCharacter::StaticClass(), PlayerActors);
}

void ABTBAIController::RunTheBehaviourTree()
{
	if(!ensure(AIBehaviorTree != nullptr))
	{
		return;
	}
	
	RunBehaviorTree(AIBehaviorTree);
}

void ABTBAIController::UpdateBlackboardClosestPlayerVariable()
{
	if(!PlayerActors.IsEmpty())
	{
		const TObjectPtr<AActor> ClosestPlayer = GetClosestPlayer();
		GetBlackboardComponent()->SetValueAsObject("PlayerActor", ClosestPlayer);
	}
}

TObjectPtr<AActor> ABTBAIController::GetClosestPlayer()
{
	if(GetPawn()->GetDistanceTo(PlayerActors[0]) < GetPawn()->GetDistanceTo(PlayerActors[1]))
	{
		return PlayerActors[0];
	}
	return PlayerActors[1];
}
