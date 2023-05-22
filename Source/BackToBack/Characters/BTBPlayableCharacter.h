// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBHumanoidCharacter.h"
#include "BTBPlayableCharacter.generated.h"

class USpringArmComponent;
class USceneCaptureComponent2D;
class UBTBCharacterJumpAction;
class UMeshComponent;
class UBoxComponent;
class UChildActorComponent;	
class ABTBGun;

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
	void SetGun(ABTBGun* Gun);
	ABTBGun* GetGun() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	bool bGunAttached;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr <UBoxComponent> CollisionBox;

	TObjectPtr<ABTBPlayableCharacter> OtherPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UChildActorComponent> GunSwitchPosition;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureCamera;



	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> DeathAnimation;

	TObjectPtr<ABTBGun> GunActor;
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FVector playersMidPoin;

	virtual void Die() override;

private:

public:

protected:
	virtual void BeginPlay() override;

};
