// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayableCharacter.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/ChildActorComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/SpringArmComponent.h"


void ABTBPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	//playersMidPoin = (GetActorLocation() + OtherPlayer->GetActorLocation()) / 2;
	
}


ABTBPlayableCharacter::ABTBPlayableCharacter()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(GetRootComponent());

	SceneCaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureCamera"));
	SceneCaptureCamera->SetupAttachment(CameraArm);
}


void ABTBPlayableCharacter::RemoveCamera() const
{
	if(SceneCaptureCamera != nullptr)
	{
		SceneCaptureCamera->DestroyComponent();
	}
}

void ABTBPlayableCharacter::AssignRenderTextureToCamera(const TObjectPtr<UTextureRenderTarget2D> RenderTarget) const
{
	if(IsValid(SceneCaptureCamera))
	{
		SceneCaptureCamera->TextureTarget = RenderTarget;
	}
	
}

void ABTBPlayableCharacter::Die()
{
	GetMesh()->PlayAnimation(DeathAnimation, false);
}




