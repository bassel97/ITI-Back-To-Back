// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBAIController.h"

#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ABTBAIController::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr && AIBehaviorTree != nullptr && PlayableCharacter != nullptr))
	{
		return;
	}

	RunBehaviorTree(AIBehaviorTree);
	
	const TObjectPtr<AActor> PlayerActor = UGameplayStatics::GetActorOfClass(World, PlayableCharacter);
	if(PlayerActor)
	{
		GetBlackboardComponent()->SetValueAsObject("PlayerActor", PlayerActor);
	}
}
