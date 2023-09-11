// @jung june


#include "SCAssetManager.h"

USCAssetManager::USCAssetManager()
{
}

USCAssetManager& USCAssetManager::Get()
{
	check(GEngine);

	if (USCAssetManager* Singleton = Cast<USCAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	SC_LOG(Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini.  It must be set to LyraAssetManager!"));

	return *NewObject<USCAssetManager>();
}

void USCAssetManager::DumpLoadedAssets()
{
	SC_LOG(Log, TEXT("========== Start Dumping Loaded Assets =========="));

	for (const UObject* LoadedAsset : Get().LoadedAssets)
	{
		SC_LOG(Log, TEXT("  %s"), *GetNameSafe(LoadedAsset));
	}

	SC_LOG(Log, TEXT("... %d assets in loaded pool"), Get().LoadedAssets.Num());
	SC_LOG(Log, TEXT("========== Finish Dumping Loaded Assets =========="));
}

UObject* USCAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		if (UAssetManager::IsValid())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		return AssetPath.TryLoad();
	}

	return nullptr;

}

void USCAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		LoadedAssets.Add(Asset);
	}
}
