// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBWeaponBase.h"

ABTBWeaponBase::ABTBWeaponBase()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
}
