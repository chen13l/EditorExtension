// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomAsset.h"

#include "AssetToolsModule.h"
#include "FAssetTypeAction_MyAsset.h"
#include "IAssetTools.h"

#define LOCTEXT_NAMESPACE "FCustomAssetModule"

void FCustomAssetModule::RegisterAssetsAction() const
{
	IAssetTools& AssetToolModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const auto Category = AssetToolModule.RegisterAdvancedAssetCategory(FName(TEXT("Custom Asset")),
	                                                                    NSLOCTEXT("Editor", "My Defined Asset", "My Custom Asset"));
	const TSharedPtr<FAssetTypeAction_MyAsset> AssetsTypeAction = MakeShareable(new FAssetTypeAction_MyAsset(Category));
	AssetToolModule.RegisterAssetTypeActions(AssetsTypeAction.ToSharedRef());
}

void FCustomAssetModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	RegisterAssetsAction();
}

void FCustomAssetModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomAssetModule, CustomAsset)
