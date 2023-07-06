// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMotorcycle.h"

#include "Kismet/GameplayStatics.h"


ABTBMotorcycle::ABTBMotorcycle()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MotorcycleSkeletalMesh"));
	SetRootComponent(SkeletalMesh);

	MaxSpeed = 2000;
	MaxSteeringAngle = 45;
	SpeedToRotationFactor = 0.001;
}

void ABTBMotorcycle::BeginPlay()
{
	Super::BeginPlay();
}

void ABTBMotorcycle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto DeltaLocation = DeltaSeconds * GetActorForwardVector() * CurrentSpeed;
	AddActorWorldOffset(DeltaLocation, true);

	/* Roll */
	const auto Roll =
		FMath::FInterpTo(CurrentLeanAngle, CurrentSteeringAngle * (CurrentSpeed / MaxSpeed), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0);

	/* Yaw */
	const auto ChangingRotation = CurrentSpeed * CurrentSteeringAngle * SpeedToRotationFactor * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	const auto ActorRot = GetActorRotation();
	const auto Yaw = ActorRot.Yaw + ChangingRotation;
	
	SetActorRelativeRotation(FRotator(0, Yaw, Roll));
	CurrentLeanAngle = Roll;
}

void ABTBMotorcycle::Steer(const float Value)
{
	CurrentSpeed = 0;
	auto Target = Value * MaxSpeed;

	CurrentSpeed =
		FMath::FInterpTo(CurrentSpeed, Target, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),4);
	
}

void ABTBMotorcycle::Throttle(const float Value)
{
	CurrentSteeringAngle = 0;
	auto Target = Value * MaxSteeringAngle;

	CurrentSteeringAngle =
		FMath::FInterpTo(CurrentSteeringAngle, Target, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),4);
}

