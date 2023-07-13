// Copyright di-tri studio, Inc. All Rights Reserved.

#include "BTBDealDamageANState.h"

#include "BackToBack/Actors/BTBSpear.h"
#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UBTBDealDamageANState::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,float FrameDeltaTime, const FAnimNotifyEventReference &EventReference)
{
  Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
  Player = Cast<ABTBMiniGameTwoPlayableCharacter>(MeshComp->GetOwner());
  TArray<AActor*> ActorsToIgnore;
  TArray<FHitResult> HitArray;
  
}

void UBTBDealDamageANState::NotifyBegin(
    USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,
    float TotalDuration, const FAnimNotifyEventReference &EventReference) {
  
  Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
  if (MeshComp && MeshComp->GetOwner()) {
    ABTBMiniGameTwoPlayableCharacter* Miles = Cast<ABTBMiniGameTwoPlayableCharacter>(MeshComp->GetOwner());
    if (Miles) {
      Miles->GetSpear()->ActivateBoxCollision();
    }
  }
}

void UBTBDealDamageANState::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,
    const FAnimNotifyEventReference &EventReference) {
  
  Super::NotifyEnd(MeshComp, Animation, EventReference);
  if (MeshComp && MeshComp->GetOwner()) {
    ABTBMiniGameTwoPlayableCharacter* Miles = Cast<ABTBMiniGameTwoPlayableCharacter>(MeshComp->GetOwner());
    if (Miles) {
      Miles->GetSpear()->DeactivateBoxCollision();
       Miles->LeftButtonState = ELeftButtonStates::None;
    }
  }
}
