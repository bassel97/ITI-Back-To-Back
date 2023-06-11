// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBDealDamageANState.h"

#include "BackToBack/Actors/BTBSpear.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UBTBDealDamageANState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitArray;
	
		UKismetSystemLibrary::SphereTraceMulti(
		MeshComp,
		MeshComp->GetRelativeLocation(),
		MeshComp->GetRelativeLocation()*5,
		5.f,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::Type::Persistent,
		HitArray,
		true,
		FColor::Red,
		FColor::Green,
		10.f
		);
		UE_LOG(LogTemp, Warning, TEXT("Inside"));
	
	//UKismetSystemLibrary::SphereTraceMulti(MeshComp, Spear->BoxTraceStart->GetRelativeLocation(), Spear->BoxTraceEnd->GetRelativeLocation(), 10, UEngineTypes::ConvertToTraceType(ECC_Pawn), true, PlayerArray, EDrawDebugTrace::Persistent, HitArray, true);
}

void UBTBDealDamageANState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpearClass, Spears);
	//Spear = Cast<ABTBSpear>(Spears[0]);
	
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	UE_LOG(LogTemp,Warning,TEXT("Begin"));

	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,TEXT("NotifyBegin"));
}

void UBTBDealDamageANState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	UE_LOG(LogTemp,Warning,TEXT("End"));
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,TEXT("NotifyEnd"));
}

UBTBDealDamageANState::UBTBDealDamageANState()
{

}


