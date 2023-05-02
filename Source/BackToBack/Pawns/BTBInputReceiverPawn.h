// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBPawn.h"
#include "BTBInputReceiverPawn.generated.h"

/**
 * Our InputReceiverPawn
 */
UCLASS()
class BACKTOBACK_API ABTBInputReceiverPawn : public ABTBPawn
{
	GENERATED_BODY()
	ABTBInputReceiverPawn();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	
public:
	UPROPERTY(VisibleAnywhere, Category="Class Variables")
	int32 PlayerIndex;

	
private:


	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera");
	float BaseTurnAtRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera");
	float BaseLookUpAtRate;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void LookUpAtRate(float Value);
	
};
