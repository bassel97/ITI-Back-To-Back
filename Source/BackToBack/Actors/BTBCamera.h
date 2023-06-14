// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBCamera.generated.h"


class ABTBPlayableCharacter;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;

/**
 * Our BTBCamera
 */
UCLASS()
class BACKTOBACK_API ABTBCamera : public ABTBActor
{
	GENERATED_BODY()
	 
public:
	ABTBCamera();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void InitCamera() const;
	void GetActivePlayers();
	void CalculateCameraLocation();
	void UpdateCameraArm();

private:
	
	
	
public:
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	
private:
	TArray<TObjectPtr<AActor>> Players;
	
	UPROPERTY(EditAnywhere, Category="Camera | Top Down Settings")
	float CameraAngle = -35;
	
	UPROPERTY(EditAnywhere, Category="Camera | Top Down Settings")
	float MinArmLength = 500;

	UPROPERTY(EditAnywhere, Category="Camera | Top Down Settings")
	float MaxArmLength = 1500;
	
	UPROPERTY(EditAnywhere, Category="Camera | Top Down Settings")
	float CameraMovementSpeed = 0.05f;
	
};
