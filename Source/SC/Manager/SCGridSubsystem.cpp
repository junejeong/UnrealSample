// @jung june


#include "SCGridSubsystem.h"

void USCGridSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USCGridSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USCGridSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);;
}
