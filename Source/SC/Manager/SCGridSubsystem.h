// @jung june

#pragma once

#include "SC.h"

#include <Subsystems/WorldSubsystem.h>

#include "SCGridSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SC_API USCGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	
};
