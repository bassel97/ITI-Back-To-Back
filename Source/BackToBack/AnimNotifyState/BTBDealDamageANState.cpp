// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBDealDamageANState.h"

#include "BackToBack/Actors/BTBSpear.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"


void UBTBDealDamageANState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	UKismetSystemLibrary::SphereTraceMulti(MeshComp, Spear->BoxTraceStart->GetRelativeLocation(), Spear->BoxTraceEnd->GetRelativeLocation(), 10, UEngineTypes::ConvertToTraceType(ECC_Pawn), true, PlayerArray, EDrawDebugTrace::Persistent, HitArray, true);

}
