// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBHumanoidCharacter.h"
#include "BTBPlayableCharacter.generated.h"

class USpringArmComponent;
class USceneCaptureComponent2D;

/**
 * Our Playable Character
 */
UCLASS()
class BACKTOBACK_API ABTBPlayableCharacter : public ABTBHumanoidCharacter
{
	GENERATED_BODY()

public:
	void AddCamera();
	
protected:

	
private:
	
	

public:

	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureCamera;
	
	
private:
	

};
