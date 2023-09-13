// @jung june


#include "SCEffectSubsystem.h"

#include <NiagaraFunctionLibrary.h>

#include "Engine/World.h"

void USCEffectSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USCEffectSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USCEffectSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return false;
}

UNiagaraComponent* USCEffectSubsystem::SpawnNiagaraSystem(UNiagaraSystem* System, FEffectParam Param, bool bAttached, bool bAbsoluteScale)
{
	UWorld* World = GetWorld();
	if (World && System)
	{

		UNiagaraComponent* NiagaraComponent = nullptr;
		if (bAttached)
		{
			NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(System, Param.MeshComp, Param.SocketName, Param.Location, Param.Rotation, EAttachLocation::KeepRelativeOffset, true);
		}
		else
		{
			NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), System, Param.Location);
		}

		if (NiagaraComponent != nullptr)
		{
			NiagaraComponent->SetUsingAbsoluteScale(bAbsoluteScale);
			NiagaraComponent->SetRelativeScale3D_Direct(Param.Scale);
			CreatedNiagaraEffects.Emplace(NiagaraComponent);

			return NiagaraComponent;
		}
	}

	return nullptr;
}

void USCEffectSubsystem::DestroyNiagaraComponent(UNiagaraComponent* NiagaraComponent)
{
	if (NiagaraComponent)
	{
		NiagaraComponent->DeactivateImmediate();
		CreatedNiagaraEffects.Remove(NiagaraComponent);
		NiagaraComponent->DestroyComponent();
	}
}
