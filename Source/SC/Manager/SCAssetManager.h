// @jung june

#pragma once

#include "SC.h"
#include "Engine/AssetManager.h"
#include "SCAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SC_API USCAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	USCAssetManager();

	static USCAssetManager& Get();

	template<typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template<typename AssetType>
	static void GetAssetAsync(const TSoftObjectPtr<AssetType>& AssetPointer, TFunctionRef<void(AssetType*)> OnLoaded, bool bKeepInMemory = true);

	template<typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	static void DumpLoadedAssets();

protected:
	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);
	void AddLoadedAsset(const UObject* Asset);

private:
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;	

	FCriticalSection LoadedAssetsCritical;
};

template<typename AssetType>
AssetType* USCAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	AssetType* LoadedAsset = nullptr;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedAsset = AssetPointer.Get();
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}

	return LoadedAsset;
}

template<typename AssetType>
void USCAssetManager::GetAssetAsync(const TSoftObjectPtr<AssetType>& AssetPointer, TFunctionRef<void(AssetType*)> OnLoaded, bool bKeepInMemory)
{
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	FStreamableDelegate OnAssetLoadedDelegate = FStreamableDelegate::CreateLambda([OnLoaded, bKeepInMemory](UObject* LoadedAsset)
		{
			if (LoadedAsset)
			{
				T* CastedAsset = Cast<T>(LoadedAsset);
				if (CastedAsset)
				{
					OnLoaded(CastedAsset);

					if (bKeepInMemory)
					{
						Get().AddLoadedAsset(LoadedAsset);
					}
				}
				else
				{
					OnLoaded(nullptr);
				}
			}
			else
			{
				OnLoaded(nullptr);
			}
		});

	Streamable.RequestAsyncLoad(AssetPath, OnAssetLoadedDelegate);
}

template<typename AssetType>
TSubclassOf<AssetType> USCAssetManager::GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to load asset class [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass && bKeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}

	return LoadedSubclass;
}
