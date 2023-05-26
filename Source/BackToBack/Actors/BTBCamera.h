// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBCamera.generated.h"


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
	
	
private:
	
	
	
public:
	FVector CameraTargetOffset;
	
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	
private:

	
};
