// @jung june

#pragma once

#include "SC.h"

#include <WorldPartition/DataLayer/DataLayerSubsystem.h>

#include "SCDataLayerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SC_API USCDataLayerSubsystem : public UDataLayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
};
