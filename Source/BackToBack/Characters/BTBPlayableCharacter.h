// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBHumanoidCharacter.h"
#include "BackToBack/Actors/BTBCamera.h"
#include "BackToBack/Vehicles/BTBVehicle.h"
#include "BTBPlayableCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

class USpringArmComponent;
class USceneCaptureComponent2D;
class UMeshComponent;
class UBoxComponent;
class UChildActorComponent;
class ABTBGun;
class UAnimMontage;


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
	void AssignRenderTextureToCamera(const TObjectPtr<UTextureRenderTarget2D> RenderTarget) const;

	virtual void SetAndResetLeftButtonEnum(const bool bIsSet)
	PURE_VIRTUAL(ABTBPlayableCharacter::SetAndResetLeftButtonEnum);

	virtual void SetAndResetRightTriggerEnum(const bool bIsSet)
	PURE_VIRTUAL(ABTBPlayableCharacter::SetAndResetRightTriggerEnum);

	virtual void SetAndResetLeftTriggerEnum(const bool bIsSet)
	PURE_VIRTUAL(ABTBPlayableCharacter::SetAndResetLeftTriggerEnum);
	
protected:
	virtual void BeginPlay() override;
	virtual void Die() override;
	
	virtual void OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
	PURE_VIRTUAL(ABTBPlayableCharacter::OnEnemyHit);
private:


	
public:
	TObjectPtr<ABTBPlayableCharacter> OtherPlayer;
	TObjectPtr<ABTBVehicle> Vehicle;

	bool bIsDead;

	UPROPERTY()
	FOnPlayerDeath OnPlayerDeath;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureCamera;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> DeathAnimation;

private:


};
