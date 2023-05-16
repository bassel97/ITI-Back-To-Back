// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBActor.h"
#include "BTBGun.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBGun : public ABTBActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;


protected:

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	bool bIsOverlapping;

public:
	ABTBGun();

	virtual void Tick(float DeltaTime) override;

	bool GetbIsOverlapping();

	void SetIsOverlapping(bool Value);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	     
private:
};
