// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBCollectables.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBCollectables : public ABTBActor
{
	GENERATED_BODY()

public:

	ABTBCollectables();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent;
};
