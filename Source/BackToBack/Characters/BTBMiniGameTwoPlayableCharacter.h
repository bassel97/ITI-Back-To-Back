// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once


#include "BTBPlayableCharacter.h"
#include "Components/TimelineComponent.h"
#include "BTBMiniGameTwoPlayableCharacter.generated.h"

class UBTBGameHUD;
class UNiagaraSystem;
class USplineMeshComponent;
class USplineComponent;
class ABTBSpear;
class UNiagaraComponent;
class UNiagaraSystem;
class UBoxComponent;
/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDashValChange, float, DashValue);

UCLASS()
class BACKTOBACK_API ABTBMiniGameTwoPlayableCharacter : public ABTBPlayableCharacter
{
  GENERATED_BODY()

public:
  ABTBMiniGameTwoPlayableCharacter();
	
  void SetSpear(ABTBSpear* Spear)
  {
  	SpearPtr = Spear;
  }

  ABTBSpear *GetSpear()
  {
  	return SpearPtr;
  }
  
  void Throw();
  void AttachSpearToPlayer();
  void Summon();
  UFUNCTION(BlueprintCallable)
  bool GetbIsAttacking();

  UFUNCTION(BlueprintCallable)
  void SetbIsAttacking(bool Value);

  UFUNCTION(BlueprintCallable)
  bool GetbIsDashing() { return bIsDashing; }

  UFUNCTION(BlueprintCallable)
  void SetbIsDashing(bool Value) { bIsDashing = Value; }
  void Dash();

protected:
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaSeconds) override;

  UFUNCTION()
  virtual void OnEnemyHit(UPrimitiveComponent *OverlappedComponent,
                          AActor *OtherActor, UPrimitiveComponent *OtherComp,
                          int32 OtherBodyIndex, bool bFromSweep,
                          const FHitResult &SweepResult) override;

  UFUNCTION()
  void OnActorHit(UPrimitiveComponent* OverlappedComponent,
	  AActor* OtherActor, UPrimitiveComponent* OtherComp,
	  int32 OtherBodyIndex, bool bFromSweep,
	  const FHitResult& SweepResult);

private:
	UFUNCTION()
		void SummonUpdate(float Alpha);
	UFUNCTION()
		void SummonFinished();

	void SummonStart();
	void SummonStop();
	void DrawSpearPath();
	void RemoveSpearPathMeshes();
	void SpawnMeshesBetweenSplinePoints();

public:
  TObjectPtr<ABTBSpear> SpearPtr;
  TObjectPtr<UBTBGameHUD> GameWidget;

  

  UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
  bool bIsThrowing;

  UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
  bool bIsSummoning;

  UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
  bool bSpearAttached;

	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		TObjectPtr<UNiagaraComponent> PlayerSpearVFX;
	
	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		TObjectPtr<UNiagaraSystem> SpearSummonVFX;
	
	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		FLinearColor SpearThrownColor;

	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		FLinearColor SpearSummonColor;

	UPROPERTY(EditAnywhere, Category = "Spear VFX")
		TObjectPtr<UCurveFloat> SummonEaseCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash Meter")
		float DashMeter = 1.0f;

  UPROPERTY()
  UAnimInstance *MilesAnimInstance;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashEffect")
  UNiagaraSystem *DashVFX;

  UPROPERTY(BlueprintAssignable, Category = "EventDispatcher")
  FOnDashValChange PlayerDash;

  UPROPERTY(EditAnywhere, Category = "Spear Retrieval Point")
	TObjectPtr<UBoxComponent> SpearRetrievalBox;

protected:
private:
	UPROPERTY(EditAnywhere, Category = "Spear Path Spline")
	TObjectPtr<USplineComponent> SplineComp;

	UPROPERTY(EditAnywhere, Category = "Spear Path Spline")
	TObjectPtr<UStaticMesh> SplineStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Spear Path Spline")
	TObjectPtr<UMaterialInstance> SplineMeshMaterial;

	UPROPERTY(EditAnywhere, Category = "Spear Path Spline")
	TObjectPtr<UStaticMeshComponent> SplineEndSphere;
	
	TArray<TObjectPtr<USplineMeshComponent>> SplineMeshComponents;

	bool bIsAttacking;

	bool bIsDashing;

	FTimeline SummonTimeline;
};
