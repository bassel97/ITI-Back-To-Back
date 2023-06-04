// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCamera.h"

#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABTBCamera::ABTBCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	SetRootComponent(CameraArm);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABTBCamera::BeginPlay()
{
	Super::BeginPlay();
	InitCamera();
	GetActivePlayers();
}

void ABTBCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CalculateCameraLocation();
	UpdateCameraArm();
}

void ABTBCamera::InitCamera() const
{
	CameraArm->TargetOffset = FVector(0, 0, MinArmLength);
	CameraArm->SetWorldRotation(FRotator(-90, 0, 0));
}
	
void ABTBCamera::GetActivePlayers()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	UGameplayStatics::GetAllActorsOfClass(World, ABTBPlayableCharacter::StaticClass(), Players);
}

void ABTBCamera::CalculateCameraLocation()
{
	const FVector CurrentCameraLocation = CameraArm->GetComponentLocation();
	const FVector PlayersAvgLocation = UGameplayStatics::GetActorArrayAverageLocation(Players);
	const FVector LerpedLocation = UKismetMathLibrary::VLerp(CurrentCameraLocation, PlayersAvgLocation, CameraMoveSpeed);
	CameraArm->SetWorldLocation(LerpedLocation);
}

void ABTBCamera::UpdateCameraArm()
{
	const float DistanceBetweenPlayers = Players[0]->GetDistanceTo(Players[1]);
	CameraArm->TargetArmLength = FMath::Clamp(DistanceBetweenPlayers, MinArmLength, MaxArmLength);
}
