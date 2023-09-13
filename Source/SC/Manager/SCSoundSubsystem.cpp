// @jung june


#include "SCSoundSubsystem.h"
#include "SCAssetManager.h"

void USCSoundSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USCSoundSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USCSoundSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void USCSoundSubsystem::PlaySound(USoundBase* Sound)
{
}

void USCSoundSubsystem::PlayBackgroundMusic(UMetaSound* BackgroundMusic)
{
}

UMetaSound* USCSoundSubsystem::LoadMetaSound(const FString& MetaSoundPath)
{
    return nullptr;
}
