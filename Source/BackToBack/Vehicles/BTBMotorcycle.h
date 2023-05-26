// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBVehicle.h"
#include "BTBMotorcycle.generated.h"

class USceneComponent;

UCLASS()
class BACKTOBACK_API ABTBMotorcycle : public ABTBVehicle
{
	GENERATED_BODY()

public:
	ABTBMotorcycle();

	void Steer(const float Value);
	void Throttle(const float Value);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	// void LookRight(const float Value);
	// void LookUp(const float Value);

private:


	
public:
	float CurrentSpeed;
	float CurrentSteeringAngle;
	float CurrentLeanAngle;
	float SpeedToRotationFactor;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	float MaxSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	float MaxSteeringAngle;

protected:

private:
	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComponent;

	
};
