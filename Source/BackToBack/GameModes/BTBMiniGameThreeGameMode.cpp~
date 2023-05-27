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
	// const TObjectPtr<AActor> MotorcycleActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABTBMotorcycle::StaticClass());
	// const TObjectPtr<ABTBMotorcycle> Motorcycle = Cast<ABTBMotorcycle>(MotorcycleActor);
	if (ensure(SpawnedVehicle != nullptr))
	{
		PlayerCharacterArray[0]->AttachToActor(SpawnedVehicle, FAttachmentTransformRules::KeepWorldTransform,TEXT("DriverSocket"));
		PlayerCharacterArray[1]->AttachToActor(SpawnedVehicle, FAttachmentTransformRules::KeepRelativeTransform,TEXT("ShooterSocket"));

		// PlayerCharacterArray[0]->AttachToComponent(Motorcycle->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform,TEXT("DriverSocket"));
		// PlayerCharacterArray[1]->AttachToComponent(Motorcycle->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform,TEXT("ShooterSocket"));
		
		PlayerCharacterArray[0]->Vehicle = SpawnedVehicle;
		//PlayerCharacterArray[1]->Vehicle = SpawnedVehicle;
		//PlayerCharacterArray[1]->Vehicle = Motorcycle;
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
		
		
		// PlayerOneSpringArm->SocketOffset = FVector(-350, 0, 200);
		// PlayerOneSpringArm->SetRelativeRotation(FRotator(-15, 90, 0));

		// PlayerTwoSpringArm->SocketOffset = FVector(0, 40, -150);
		// PlayerTwoSpringArm->SetRelativeRotation(FRotator(-25, 90, 0));
		// PlayerTwoSpringArm->SetRelativeLocation(FVector(0, 40, -150));

		
		PlayerOneSpringArm->SocketOffset = FVector(0, 0, 0);
		PlayerOneSpringArm->SetRelativeRotation(FRotator(-20, 90, 0));

		PlayerTwoSpringArm->SocketOffset = FVector(0, 65, 75);
		
	}
}
