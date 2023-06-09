// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBSpear.h"
#include "Components/BoxComponent.h"

ABTBSpear::ABTBSpear()
{
	SpearMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spear Mesh"));
	SpearMesh->SetupAttachment(SceneComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(SceneComponent);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace BoxTraceStart"));
	BoxTraceStart->SetupAttachment(SpearMesh);

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(SpearMesh);
}
