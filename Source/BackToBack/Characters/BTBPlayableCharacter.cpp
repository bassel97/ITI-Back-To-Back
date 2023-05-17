// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayableCharacter.h"

#include "BackToBack/Actions/BTBCharacterJumpAction.h"
#include "BackToBack/Actors/BTBGun.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ABTBPlayableCharacter::ABTBPlayableCharacter()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(GetRootComponent());

	SceneCaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureCamera"));
	SceneCaptureCamera->SetupAttachment(CameraArm);

	//mySkeleton = GetMesh()->GetSkinnedAsset();

	//mySkeleton->Sockets.Empty(); //Clears all sockets
	//mySkeleton->Modify(); //Not sure what this does but it is needed.
	//mySocket->SocketName = FName("mySocket"); //Obviously sets the sockets name
	//mySocket->BoneName = FName("hand_r"); //Attaches to the bone you choose
	//mySkeleton->Sockets.Add(mySocket); //Finally adds the socket to the skeleton
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



void ABTBPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	//TArray<TObjectPtr<AActor>> ActorsGuns;

	//Switching Related
	
	
	
	

	
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), GunActorClass, ActorsGuns);

	//GunActor = Cast<ABTBGun>(ActorsGuns[0]);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switching %d", GunActor));

	//if (GunActor)
	//{
	//	GunActor->SetIsOverlapping(true);
	//}
	//
	//GunActor->SetIsOverlapping(true);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switching"));
	
}




void ABTBPlayableCharacter::AssignRenderTextureToCamera(const TObjectPtr<UTextureRenderTarget2D> RenderTarget)
{
	if(IsValid(SceneCaptureCamera))
	{
		SceneCaptureCamera->TextureTarget = RenderTarget;
	}
	
}

void ABTBPlayableCharacter::GetGunFromGameplayMode(ABTBGun* Gun)
{
	GunActor = Gun;
}

ABTBGun* ABTBPlayableCharacter::GetGun()
{
	return GunActor;
}




