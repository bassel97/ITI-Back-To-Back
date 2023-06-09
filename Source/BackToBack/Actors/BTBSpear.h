// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBWeaponBase.h"
#include "BTBSpear.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBSpear : public ABTBWeaponBase
{
	GENERATED_BODY()

public:
	ABTBSpear();

	UPROPERTY(VisibleAnywhere)
		USceneComponent* BoxTraceStart;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* BoxTraceEnd;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> SpearMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> CollisionBox;



private:


};
