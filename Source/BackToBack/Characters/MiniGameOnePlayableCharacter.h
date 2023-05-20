// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPlayableCharacter.h"
#include "MiniGameOnePlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API AMiniGameOnePlayableCharacter : public ABTBPlayableCharacter
{
	GENERATED_BODY()

public:

protected:
	//virtual float GetRotationValue() override;
	//virtual void BeginPlay() override;
	virtual void Die() override;
	UFUNCTION()
		void OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

};
