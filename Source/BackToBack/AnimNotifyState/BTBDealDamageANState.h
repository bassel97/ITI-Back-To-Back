// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBAnimNotifyState.h"
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
	UBTBDealDamageANState();


public:
	ABTBSpear* Spear;
	TArray<AActor*> Spears;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spear")
	TSubclassOf<ABTBSpear> SpearClass;
	//TArray<FHitResult> HitArray;
	TArray<AActor*> PlayerArray;
};
