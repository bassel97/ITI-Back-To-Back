// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABTBCamera::ABTBCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	SetRootComponent(CameraArm);
			
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	

	CameraArm->TargetOffset = FVector(387.0, 3471.0, 190.0);
}
