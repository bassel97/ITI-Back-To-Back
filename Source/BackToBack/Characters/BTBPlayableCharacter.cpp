// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayableCharacter.h"
#include "BackToBack/Actors/BTBGun.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"


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

void ABTBPlayableCharacter::SetGun(ABTBGun* Gun)
{
	GunActor = Gun;
}

ABTBGun* ABTBPlayableCharacter::GetGun() const
{
	return GunActor;
}

void ABTBPlayableCharacter::Die()
{
	GetMesh()->PlayAnimation(DeathAnimation, false);
}




