// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayableCharacter.h"

#include "BackToBack/Actions/BTBCharacterJumpAction.h"
#include "Camera/CameraComponent.h"
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

void ABTBPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void ABTBPlayableCharacter::BeginPlay()
//{
//	Super::BeginPlay();
//	//JumpAction = NewObject<UBTBCharacterJumpAction>(this, UBTBCharacterJumpAction::StaticClass());
//	//JumpAction = Cast<UBTBCharacterJumpAction>(CharacterActionClass);
//	
//	CharacterActions.AddUnique(JumpAction);
//}

void ABTBPlayableCharacter::AssignRenderTextureToCamera(const TObjectPtr<UTextureRenderTarget2D> RenderTarget)
{
	if(IsValid(SceneCaptureCamera))
	{
		SceneCaptureCamera->TextureTarget = RenderTarget;
	}
}




