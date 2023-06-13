// Copyright di-tri studio, Inc. All Rights Reserved.


#include "MilesAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMilesAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Miles = Cast<ABTBMiniGameTwoPlayableCharacter>(TryGetPawnOwner());
	if (Miles)
	{
		MilesMovementComponent = Miles->GetCharacterMovement();

	}
}

void UMilesAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (MilesMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MilesMovementComponent->Velocity);
	}
	if (Miles)
	{
		bThrow = Miles->bIsThrowing;
		bAttack = Miles->GetbIsAttacking();
	}

}