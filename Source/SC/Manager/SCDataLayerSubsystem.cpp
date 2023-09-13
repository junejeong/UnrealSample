// @jung june


#include "SCDataLayerSubsystem.h"

void USCDataLayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USCDataLayerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USCDataLayerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}
