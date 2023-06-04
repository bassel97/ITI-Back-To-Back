// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBGameplayGameMode.h"
#include "BTBMiniGameOneGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBMiniGameOneGameMode : public ABTBGameplayGameMode
{
	GENERATED_BODY()
	
public:

protected:
	virtual void BeginPlay() override;
	
	void AssignGunToPlayer();

private:

	

public:

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Player Weapons")
	TSubclassOf<ABTBGun> GunClass;	                        
                                                            
	TObjectPtr<ABTBGun> Gun;                                

private:
	
};
