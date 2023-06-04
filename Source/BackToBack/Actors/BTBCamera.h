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

	void InitCamera();
	void GetActivePlayers();
	void CalculateCameraMovement();
	void UpdateCameraMovement();

private:
	
	
	
public:
	FVector CameraTargetOffset;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	
private:
	TArray<TObjectPtr<AActor>> ActivePlayers;
	TArray<float> Distances;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	float MinArmLength/* = 500*/;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	float MaxArmLength/* = 1500*/;
	
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	float CameraMoveSpeed/* = 0.05f*/;
	
};
