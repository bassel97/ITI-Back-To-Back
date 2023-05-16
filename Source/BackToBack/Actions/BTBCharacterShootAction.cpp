// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterShootAction.h"
#include "BackToBack/Actors/BTBObjectPoolComponent.h"
#include "BackToBack/Actors/BTBGun.h"
#include "BackToBack/Characters/BTBCharacter.h"

void UBTBCharacterShootAction::Act(ABTBCharacter* Character, const bool bIsAI)
{
	
	if(!bIsAI)
	{
		if (Character == nullptr)
		{
			return;
		}
		if (Character->GetbStartPool())
		{
			Bullet = Cast<UBTBObjectPoolComponent>(Character->GetDefaultSubobjectByName(FName("BTBObjectPool")));
			//Gun = Cast<ABTBGun>(GunClass);
			

		}
		if (Character->GetbStartShoot())
		{
			
	#pragma region Shooting using player
			if (Bullet)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, TEXT("We are shooting"));
					UE_LOG(LogTemp, Warning, TEXT("We are shooting"));
				}
				const FVector ShootingOffset = FVector(100.f, 0, 0);
				const FVector SpawnPos = Character->GetActorLocation() + ShootingOffset;
				Bullet->SpawnPooledObject(SpawnPos, FRotator().ZeroRotator);
				Character->SetbStartShoot(false);
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, TEXT("Bullet is nullptr"));
					UE_LOG(LogTemp, Warning, TEXT("Bullet is nullptr"));
				}
			}
		#pragma endregion

	#pragma region Shooting using Gun
			/*if (Gun)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, TEXT("We are shooting"));
					UE_LOG(LogTemp, Warning, TEXT("Gun is shooting"));
				}
				const FVector ShootingOffset = FVector(100.f, 0, 0);
				const FVector SpawnPos = Character->GetActorLocation() + ShootingOffset;
				Gun->Shoot();
				Character->SetbStartShoot(false);
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, TEXT("Gun is nullptr"));
					UE_LOG(LogTemp, Warning, TEXT("Bullet is nullptr"));
				}
			}*/
		#pragma endregion

		}
	}
	else
	{
		
	}
	
}



