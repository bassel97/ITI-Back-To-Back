// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCharacterRotateAction.h"

#include "GameFramework/PawnMovementComponent.h"
#include "BackToBack/Characters/BTBCharacter.h"


void UBTBCharacterRotateAction::Act(ABTBCharacter* Character)
{
	if (Character == nullptr)
	{
		return;
	}

	if (Character->GetbStartRotate())
	{

		FVector CurrentLocation = Character->GetActorLocation();
		float RotationValue = Character->GetRotationValue();
		//Character->AddControllerYawInput(RotationValue);
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
		FVector Radius = FVector(5.f * orientation, 0 * orientation, 0);
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


