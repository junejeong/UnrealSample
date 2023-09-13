// @jung june

#pragma once

#include "SC.h"
#include "Subsystems/WorldSubsystem.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "SCEffectSubsystem.generated.h"

/**
 * 
 */
 struct FEffectParam
 {
     USceneComponent* MeshComp;
     FName SocketName;
     FVector Location;
     FRotator Rotation;
     FVector Scale;
 };

UCLASS()
class SC_API USCEffectSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
    USCEffectSubsystem();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

public:
    UNiagaraComponent* SpawnNiagaraSystem(UNiagaraSystem* System, FEffectParam Param, bool bAttached, bool bAbsoluteScale);
    void DestroyNiagaraComponent(UNiagaraComponent* NiagaraComponent);

private:
    TArray<UNiagaraComponent*> CreatedNiagaraEffects;
};
