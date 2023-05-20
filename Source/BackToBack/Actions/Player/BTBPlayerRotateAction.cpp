// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBPlayerRotateAction.h"

#include "BackToBack/AIControllers/BTBAIController.h"
#include "BackToBack/Characters/BTBCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


void UBTBPlayerRotateAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}
	
	const float RotationValue = Character->GetRotationValue();
	const FTransform CharacterTransform = Character->GetTransform();
	
	const FVector RelativeCenterOfRotationWS = CharacterTransform.TransformVector(RelativeCenterOfRotation);
	const FTransform LocalRotateCenter = FTransform(CharacterTransform.GetRotation(), RelativeCenterOfRotationWS);

	Character->SetActorTransform(LocalRotateCenter.Inverse() * Character->GetTransform());
	Character->AddActorLocalRotation(FRotator(0, RotationValue, 0));
	Character->SetActorTransform(LocalRotateCenter * Character->GetTransform());

	//Debugging
#if UE_EDITOR
		//UE_LOG(LogTemp, Warning, TEXT("Yaw angle is : %f"), Character->GetActorRotation().Yaw);
#endif
	
}


