// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once


#include "BTBPlayableCharacter.h"
#include "CoreMinimal.h"
#include "BTBMiniGameTwoPlayableCharacter.generated.h"

class UBTBGameHUD;
class UNiagaraSystem;
class ABTBSpear;
/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDashValChange, float, DashValue);

UCLASS()
class BACKTOBACK_API ABTBMiniGameTwoPlayableCharacter
    : public ABTBPlayableCharacter {
  GENERATED_BODY()

public:
  ABTBMiniGameTwoPlayableCharacter();
  void SetSpear(ABTBSpear *Spear);
  ABTBSpear *GetSpear();
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
  virtual void Die() override;

  UFUNCTION()
  virtual void OnEnemyHit(UPrimitiveComponent *OverlappedComponent,
                          AActor *OtherActor, UPrimitiveComponent *OtherComp,
                          int32 OtherBodyIndex, bool bFromSweep,
                          const FHitResult &SweepResult) override;

private:
public:
  TObjectPtr<ABTBSpear> SpearPtr;
  TObjectPtr<UBTBGameHUD> GameWidget;

  UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
  bool bIsThrowing;

  UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
  bool bIsSummoning;

  UPROPERTY(BlueprintReadOnly, Category = "Throw Spear")
  bool bSpearAttached;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash Meter")
  float DashMeter = 1.0f;

  bool bIsoverlappingCollectable;

  UPROPERTY()
  UAnimInstance *MilesAnimInstance;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashEffect")
  UNiagaraSystem *DashVFX;

  UPROPERTY(BlueprintAssignable, Category = "EventDispatcher")
  FOnDashValChange PlayerDash;

protected:
private:
  UPROPERTY(EditAnywhere, Category = "Spear Retrieval Point")
  TObjectPtr<USceneComponent> SpearRetrievalPoint;

  bool bIsAttacking;

  bool bIsDashing;
};
