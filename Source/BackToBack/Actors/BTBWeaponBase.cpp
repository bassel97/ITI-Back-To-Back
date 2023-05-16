// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBWeaponBase.h"

ABTBWeaponBase::ABTBWeaponBase()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
}
