// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBDataAsset.h"
#include "BTBSplitScreenDataAsset.generated.h"

/**
 * Our Split Screen Data Asset
 */

UENUM()
enum class ECameraMode : uint8
{
	SingleCamera,
	SplitScreen
};

UCLASS()
class BACKTOBACK_API UBTBSplitScreenDataAsset final : public UBTBDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Global Game Screen Mode")
	ECameraMode CameraMode;
	
};
