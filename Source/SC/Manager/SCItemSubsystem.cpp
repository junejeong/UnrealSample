// @jung june


#include "SCItemSubsystem.h"

void USCItemSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USCItemSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USCItemSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}
