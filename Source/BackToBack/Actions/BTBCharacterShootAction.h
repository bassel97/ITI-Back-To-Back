// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBCharacterAction.h"


#include "BTBCharacterShootAction.generated.h"

class UBTBObjectPoolComponent;
class ABTBGun;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBCharacterShootAction : public UBTBCharacterAction
{
	GENERATED_BODY()
public:

	virtual void Act(ABTBCharacter* Character, const bool bIsAI) override;
	/*UFUNCTION()
		void OnPooledObjectDespawn(ABTBPooledObject* PooledActor);*/
	UPROPERTY(EditDefaultsOnly)
		FVector SpawnPosition;
	UPROPERTY(EditDefaultsOnly)
		FRotator BulletOrientation;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UBTBObjectPoolComponent> BulletClass;
	//
	//	//TObjectPtr<UBTBObjectPoolComponent> Bullet;
	UBTBObjectPoolComponent* Bullet;

	/*UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABTBGun> GunClass;
	ABTBGun* Gun;*/


};
