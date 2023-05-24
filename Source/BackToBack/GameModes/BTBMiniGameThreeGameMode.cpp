// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameThreeGameMode.h"

#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "BackToBack/Vehicles/BTBMotorcycle.h"
#include "Kismet/GameplayStatics.h"

void ABTBMiniGameThreeGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnMotorcycle();
	SetPlayersAsChildOfMotorcycle();
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
		World->SpawnActor<ABTBMotorcycle>(MotorcycleClass, PlayerCharacterArray[0]->GetActorLocation(), PlayerCharacterArray[0]->GetActorRotation(), SpawnParams);

}

void ABTBMiniGameThreeGameMode::SetPlayersAsChildOfMotorcycle()
{
	//const TObjectPtr<AActor> MotorcycleActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABTBMotorcycle::StaticClass());
	//const TObjectPtr<ABTBMotorcycle> Motorcycle = Cast<ABTBMotorcycle>(MotorcycleActor);
	if (ensure(SpawnedVehicle != nullptr))
	{
		PlayerCharacterArray[0]->AttachToActor(SpawnedVehicle, FAttachmentTransformRules::KeepWorldTransform,TEXT("DriverSocket"));
		PlayerCharacterArray[1]->AttachToActor(SpawnedVehicle, FAttachmentTransformRules::KeepWorldTransform,TEXT("ShooterSocket"));
		
		PlayerCharacterArray[0]->Vehicle = SpawnedVehicle;
		PlayerCharacterArray[1]->Vehicle = SpawnedVehicle;
		//PlayerCharacterArray[1]->Vehicle = Motorcycle;
	}
}
