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
		//UE_LOG(LogTemp, Warning, TEXT("We are rotating, we are sinking"));
		//FRotator CharRotation = Character->GetActorRotation();

		//FRotator NewRotation = CharRotation.Add(0, Character->GetRotationValue() , 0);

		FRotator NewRotation = FRotator(0, Character->GetRotationValue(), 0);

		FQuat QuatRotation = FQuat(NewRotation);

		Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		//FRotator Rotation = Character->GetControlRotation();
		//FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		//if(Character->GetController())
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("This bitch has a PlayerController"));
		//}
		//Character->AddControllerYawInput(/*YawRotation.*/Character->GetRotationValue());
		//Character->AddControllerYawInput(NewRotation.Yaw);
		
		
		UE_LOG(LogTemp, Warning, TEXT("Yaw angle is , %f"), Character->GetActorRotation().Yaw);
		/*UE_LOG(LogTemp, Warning, TEXT("Deprecated Yaw input scale is , %f"), Character->GetC);*/
		
	}





}


