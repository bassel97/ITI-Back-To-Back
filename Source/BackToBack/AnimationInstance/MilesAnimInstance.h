// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MilesAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UMilesAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly)
	class ABTBMiniGameTwoPlayableCharacter* Miles;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	class UCharacterMovementComponent* MilesMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;
		
	UPROPERTY(BlueprintReadOnly, Category = "Throwing")
	bool bThrow;

	UPROPERTY(BlueprintReadWrite, Category = "Throwing")
	bool bAttack;
};
