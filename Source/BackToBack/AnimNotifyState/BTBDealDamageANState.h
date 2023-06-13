// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBAnimNotifyState.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "BTBDealDamageANState.generated.h"

class ABTBSpear;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBDealDamageANState : public UBTBAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	TObjectPtr<ABTBMiniGameTwoPlayableCharacter> Player;
public:
	// ABTBSpear* Spear;
	// TArray<AActor*> Spears;
	//
	// //ABTBMiniGameTwoPlayableCharacter* player;
	//
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spear")
	// TSubclassOf<ABTBSpear> SpearClass;


};
