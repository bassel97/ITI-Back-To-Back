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
#pragma region AddingControllerAndRotating
	//Character->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
//Character->AutoPossessPlayer = EAutoReceiveInput::Player2;
//Character->AutoReceiveInput = EAutoReceiveInput::Player0;
//if(Character->GetController())
//{
//	UE_LOG(LogTemp, Warning, TEXT("We assigned a controller to the player and it's name is %s"),*Character->GetController()->GetName());
//	
//	//Character->GetController()
//	Character->bUseControllerRotationYaw = true;
//	Character->AddControllerYawInput(RotationValue);
//}
	//When passing the yaw angle if we rotated the input receiver
	/*Character->SetActorRotation(FRotator(0.f,Character->GetRotationValue(),0.f));
	UE_LOG(LogTemp, Warning, TEXT("Input Value is : %f"), RotationValue);*/
#pragma endregion

	if (Character->GetbStartRotate())
	{
		FVector CurrentLocation = Character->GetActorLocation();
		float RotationValue = Character->GetRotationValue();

		int32 orientation;
		if (RotationValue > 0)
		{
			orientation = -1;
		}
		else
		{
			orientation = 1;
		}
		
		Angle += RotationValue;
		if (Angle > 360.0f) Angle = 1;

		//Rotation around an offset (Radius)
		FVector Radius = FVector(XCenterOfRotation * orientation, 0 * orientation, 0);
		FVector RotatedRadius = Radius.RotateAngleAxis(Angle, FVector(0, 0, 1));
		CurrentLocation.X += RotatedRadius.X;
		CurrentLocation.Y += RotatedRadius.Y;
		CurrentLocation.Z += RotatedRadius.Z;

		//Orientation
		FRotator NewRotation = FRotator(0, RotationValue, 0);
		FQuat QuatRotation = FQuat(NewRotation);

		//Applying the rotation
		Character->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		Character->SetActorLocation(CurrentLocation);

		//Debugging
#if UE_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Yaw angle is : %f"), Character->GetActorRotation().Yaw);
		UE_LOG(LogTemp, Warning, TEXT("Rotation Angle is : %f"), Angle);
		UE_LOG(LogTemp, Warning, TEXT("Input Value is : %f"), RotationValue);
#endif
	}
	

	
}


