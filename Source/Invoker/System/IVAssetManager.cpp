// Copyright Epic Games, Inc. All Rights Reserved.

#include "IVAssetManager.h"
#include "Stats/StatsMisc.h"
#include "Engine/Engine.h"
#include "Invoker/IVLogChannels.h"


const FPrimaryAssetType	UIVAssetManager::SkillItem = TEXT("SkillItem");

const FPrimaryAssetType	UIVAssetManager::PotionItemType = TEXT("Potion");
const FPrimaryAssetType	UIVAssetManager::TokenItemType = TEXT("Token");
const FPrimaryAssetType	UIVAssetManager::WeaponItemType = TEXT("Weapon");

//////////////////////////////////////////////////////////////////////
UIVAssetManager::UIVAssetManager()
{
}

UIVAssetManager& UIVAssetManager::Get()
{
	check(GEngine);

	if (UIVAssetManager* Singleton = Cast<UIVAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogInvoker, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini.  It must be set to LyraAssetManager!"));

	// Fatal error above prevents this from being called.
	return *NewObject<UIVAssetManager>();
}

UObject* UIVAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;

		if (ShouldLogAssetLoads())
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronously loaded asset [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		if (UAssetManager::IsValid())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		// Use LoadObject if asset manager isn't ready yet.
		return AssetPath.TryLoad();
	}

	return nullptr;
}

bool UIVAssetManager::ShouldLogAssetLoads()
{
	static bool bLogAssetLoads = FParse::Param(FCommandLine::Get(), TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

void UIVAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		LoadedAssets.Add(Asset);
	}
}

void UIVAssetManager::DumpLoadedAssets()
{
	UE_LOG(LogInvoker, Log, TEXT("========== Start Dumping Loaded Assets =========="));

	for (const UObject* LoadedAsset : Get().LoadedAssets)
	{
		UE_LOG(LogInvoker, Log, TEXT("  %s"), *GetNameSafe(LoadedAsset));
	}

	UE_LOG(LogInvoker, Log, TEXT("... %d assets in loaded pool"), Get().LoadedAssets.Num());
	UE_LOG(LogInvoker, Log, TEXT("========== Finish Dumping Loaded Assets =========="));
}

void UIVAssetManager::UpdateInitialGameContentLoadPercent(float GameContentPercent)
{
	// Could route this to the early startup loading screen
}

