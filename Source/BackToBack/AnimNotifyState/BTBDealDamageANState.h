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

public:
	ABTBSpear* Spear;
	TArray<FHitResult> HitArray;
	TArray<AActor*> PlayerArray;
};
