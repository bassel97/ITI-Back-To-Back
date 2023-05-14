// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterShootAction.h"
#include "BackToBack/Actors/BTBObjectPoolComponent.h"
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

		}
		if (Character->GetbStartShoot())
		{
			/*auto Bullet = Character->GetComponentByClass(BulletClass);
			auto AnotherBullet = Cast<UBTBObjectPoolComponent>(BulletClass);*/
			
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
			
			
			
			
		}
	}
	else
	{
		
	}
	
}



