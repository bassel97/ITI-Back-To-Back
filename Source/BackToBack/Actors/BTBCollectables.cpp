// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCollectables.h"

ABTBCollectables::ABTBCollectables()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
}
