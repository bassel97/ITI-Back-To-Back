// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBCollectables.h"
#include "BTBScarabCollectable.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBScarabCollectable : public ABTBCollectables
{
	GENERATED_BODY()

public:
ABTBScarabCollectable();
	UFUNCTION()
void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;


private:


public:
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ScarabMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Components")
	TObjectPtr<UBoxComponent> CollisionBox;
private:
};
