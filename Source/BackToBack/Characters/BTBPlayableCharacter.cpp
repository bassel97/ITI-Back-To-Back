// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayableCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"

void ABTBPlayableCharacter::AddCamera()
{
	CameraArm = NewObject<USpringArmComponent>(this, USpringArmComponent::StaticClass(),TEXT("CameraArm"));
	
	SceneCaptureCamera = NewObject<USceneCaptureComponent2D>(this, USceneCaptureComponent2D::StaticClass(),TEXT("SceneCaptureCamera"));
	
	if(!ensure(CameraArm != nullptr && SceneCaptureCamera != nullptr))
	{
		return;
	}
	
	CameraArm->SetupAttachment(RootComponent.Get());
	SceneCaptureCamera->SetupAttachment(CameraArm);
	
	CameraArm->RegisterComponent();
	SceneCaptureCamera->RegisterComponent();
}
