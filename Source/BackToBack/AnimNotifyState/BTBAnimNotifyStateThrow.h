// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBAnimNotifyState.h"
#include "BTBAnimNotifyStateThrow.generated.h"


class ABTBMiniGameTwoPlayableCharacter;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBAnimNotifyStateThrow : public UBTBAnimNotifyState
{
	GENERATED_BODY()

		//Variables
public:
	TObjectPtr<ABTBMiniGameTwoPlayableCharacter> Miles;
protected:

private:


	//Functions
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
