// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameThreeGameMode.h"

#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/DataAssets/BTBSplitScreenDataAsset.h"
#include "BackToBack/Vehicles/BTBMotorcycle.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

void ABTBMiniGameThreeGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnMotorcycle();
	SetPlayersAsChildOfMotorcycle();
	AdjustPlayersCameras();
}

void ABTBMiniGameThreeGameMode::SpawnMotorcycle()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	
	if(!ensure(MotorcycleClass != nullptr))
	{
		return;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	SpawnedVehicle =
		World->SpawnActor<ABTBMotorcycle>(MotorcycleClass, FVector::Zero(), FRotator::ZeroRotator/*, SpawnParams*/);

}

void ABTBMiniGameThreeGameMode::SetPlayersAsChildOfMotorcycle()
{
	if (ensure(SpawnedVehicle != nullptr))
	{
		PlayerCharacterArray[0]->AttachToActor(SpawnedVehicle, FAttachmentTransformRules::KeepWorldTransform,TEXT("DriverSocket"));
		PlayerCharacterArray[1]->AttachToActor(SpawnedVehicle, FAttachmentTransformRules::KeepRelativeTransform,TEXT("ShooterSocket"));
		PlayerCharacterArray[0]->Vehicle = SpawnedVehicle;
	}
}

void ABTBMiniGameThreeGameMode::AdjustPlayersCameras()
{
	if(SplitScreenClass->CameraMode == ECameraMode::SplitScreen)
	{
		const auto PlayerOneActorComponent = PlayerCharacterArray[0]->GetComponentByClass(USpringArmComponent::StaticClass());
		const auto PlayerOneSpringArm = Cast<USpringArmComponent>(PlayerOneActorComponent);

		const auto PlayerTwoActorComponent = PlayerCharacterArray[1]->GetComponentByClass(USpringArmComponent::StaticClass());
		const auto PlayerTwoSpringArm = Cast<USpringArmComponent>(PlayerTwoActorComponent);
		
		PlayerOneSpringArm->SocketOffset = FVector(0, 0, 0);
		PlayerOneSpringArm->SetRelativeRotation(FRotator(-20, 90, 0));

		PlayerTwoSpringArm->SocketOffset = FVector(0, 65, 75);
		
	}
}
