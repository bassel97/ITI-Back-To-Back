// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterRotateAction.h"

#include "GameFramework/PawnMovementComponent.h"


void UBTBCharacterRotateAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}

	if (Character->GetbStartRotate())
	{

		FRotator NewRotation = FRotator(0, Character->GetRotationValue(), 0);

		FQuat QuatRotation = FQuat(NewRotation);
		Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		
		//Character->GetController()->SetControlRotation(NewRotation);
		
		/*if(APlayerController* PC = Cast<APlayerController>(Character))
		{
			PC->Possess(Character);
			Character->AddControllerYawInput(Character->GetRotationValue());
			PC->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Using On-the-fly Controller"));
		}
		else
		{
			Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
			UE_LOG(LogTemp, Warning, TEXT("Using Actor Rotation"));
		}*/
		/*if(Character->GetController())
		{
			Character->AddControllerYawInput(Character->GetRotationValue());
			UE_LOG(LogTemp, Warning, TEXT("Using Actor Controller"));
		}
		else
		{
			Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
			UE_LOG(LogTemp, Warning, TEXT("Using Actor Rotation"));
		}*/
		UE_LOG(LogTemp, Warning, TEXT("Yaw angle is : %f"), Character->GetActorRotation().Yaw);
		
	}





}


