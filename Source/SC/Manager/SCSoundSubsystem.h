// @jung june

#pragma once

#include "SC.h"
#include "SCAssetManager.h"

#include <Sound/SoundBase.h>
#include <Subsystems/GameInstanceSubsystem.h>

#include "SCSoundSubsystem.generated.h"

UCLASS()
class SC_API USCSoundSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

public:
    void PlaySound(USoundBase* Sound);
    void PlayFootstepSound();
};
