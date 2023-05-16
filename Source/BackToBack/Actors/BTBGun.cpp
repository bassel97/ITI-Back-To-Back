// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBGun.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


ABTBGun::ABTBGun()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	GunMesh->SetupAttachment(SceneComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereCollider"));
	CollisionBox->SetupAttachment(GunMesh);
}

void ABTBGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTBGun::BeginPlay()
{
	Super::BeginPlay();
}

void ABTBGun::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetIsOverlapping(true);
}

void ABTBGun::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetIsOverlapping(false);
}

bool ABTBGun::GetbIsOverlapping()
{
	return bIsOverlapping;
}

void ABTBGun::SetIsOverlapping(bool Value)
{
	bIsOverlapping = Value;
}