// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBPlayerShootAction.generated.h"

class UBTBObjectPoolComponent;
class ABTBGun;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBPlayerShootAction : public UBTBCharacterAction
{
	GENERATED_BODY()
public:

	virtual void Act(ABTBCharacter* Character) override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBTBObjectPoolComponent> BulletClass;
	
	TObjectPtr<ABTBGun> Gun;


};
