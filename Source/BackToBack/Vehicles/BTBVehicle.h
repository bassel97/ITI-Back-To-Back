// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BTBVehicle.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;

UCLASS()
class BACKTOBACK_API ABTBVehicle : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

private:
	
};
