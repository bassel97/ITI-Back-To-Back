// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayableCharacter.h"
#include "BackToBack/Actors/BTBGun.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/SpringArmComponent.h"


void ABTBPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABTBPlayableCharacter::OnBoxOverlap);
	//CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABTBPlayableCharacter::OnBoxEndOverlap);

	//playersMidPoin = (GetActorLocation() + OtherPlayer->GetActorLocation()) / 2;
	
}


ABTBPlayableCharacter::ABTBPlayableCharacter()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(GetRootComponent());

	SceneCaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureCamera"));
	SceneCaptureCamera->SetupAttachment(CameraArm);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	//CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetAllMassScale(0.5);
	CollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");

	GunSwitchPosition = CreateDefaultSubobject<UChildActorComponent>(TEXT("GunSwitchPosition"));
	GunSwitchPosition->SetupAttachment(GetMesh());
	//GunSwitchPosition->SetRelativeLocation(playersMidPoin);
	


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

ABTBGun* ABTBPlayableCharacter::GetGun()
{
	return GunActor;
}

void ABTBPlayableCharacter::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Gun"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Other Actor: %s, Other Comp: %s"))
		this->SetbStartSwitching(true);
		//IsOverlapping = true;
		UE_LOG(LogTemp, Warning, TEXT("OverLapping"));
	}

}

//void ABTBPlayableCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	IsOverlapping = false;
//}

void ABTBPlayableCharacter::Die()
{
	GetMesh()->PlayAnimation(DeathAnimation, false);
}




