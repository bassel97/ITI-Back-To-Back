// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBWeaponBase : public ABTBActor
{
	GENERATED_BODY()

protected:
	ABTBWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* SceneComponent;

	
	
};
