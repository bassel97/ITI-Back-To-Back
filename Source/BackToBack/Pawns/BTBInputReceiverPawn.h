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
	void Start();

	
protected:
#pragma region UPROPERTIES
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera");
	float BaseTurnAtRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera");
	float BaseLookUpAtRate;

#pragma endregion UPROPERTIES

#pragma region UFUNCTIONS
	
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void LookUpAtRate(float Value);

#pragma endregion UFUNCTIONS
};
