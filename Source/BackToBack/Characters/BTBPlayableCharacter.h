// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBHumanoidCharacter.h"
#include "BackToBack/Actions/BTBCharacterAction.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BTBPlayableCharacter.generated.h"

class USpringArmComponent;
class USceneCaptureComponent2D;
class UBTBCharacterJumpAction;
class ABTBGun;
//class UBTBCharacterAction;

/**
 * Our Playable Character
 */
UCLASS()
class BACKTOBACK_API ABTBPlayableCharacter : public ABTBHumanoidCharacter
{
	GENERATED_BODY()

public:
	ABTBPlayableCharacter();
	void RemoveCamera() const;
	void AssignRenderTextureToCamera(const TObjectPtr<UTextureRenderTarget2D> RenderTarget);
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
	
private:
	
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	bool bGunAttached;

	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureCamera;

	//USkeleton* mySkeleton;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	USkeleton* mySkeleton = CreateDefaultSubobject<USkeleton>(TEXT("mySkeleton"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	USkeletalMeshSocket* mySocket = NewObject<USkeletalMeshSocket>(mySkeleton);*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AActor> GunActorClass;

	TObjectPtr<ABTBGun> GunActor;



	//UPROPERTY(EditDefaultsOnly,Category="Actions")
	///*TObjectPtr<UBTBCharacterAction> CharacterActionClass;*/

	//TObjectPtr<UBTBCharacterJumpAction> JumpAction;
private:
	

};
