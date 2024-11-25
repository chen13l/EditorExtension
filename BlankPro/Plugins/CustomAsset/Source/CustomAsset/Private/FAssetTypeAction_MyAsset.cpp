#include "FAssetTypeAction_MyAsset.h"

#include "AssetObject.h"
#include "AssetEditor/MyAssetEditorToolkit.h"

FAssetTypeAction_MyAsset::FAssetTypeAction_MyAsset(EAssetTypeCategories::Type Category) : MyAssetCategory(Category)
{
}

FText FAssetTypeAction_MyAsset::GetName() const
{
	return NSLOCTEXT("Editor", "My Asstes Name", "My Custom Asset");
}

FColor FAssetTypeAction_MyAsset::GetTypeColor() const
{
	return FColor::Green;
}

UClass* FAssetTypeAction_MyAsset::GetSupportedClass() const
{
	return UAssetObject::StaticClass();
}

void FAssetTypeAction_MyAsset::OpenAssetEditor(const TArray<UObject*>& InObjects, const EAssetTypeActivationOpenedMethod OpenedMethod,
                                               TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type ToolKitModeType = EditWithinLevelEditor ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	//FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
	for (auto Object : InObjects)
	{
		if (UAssetObject* AssetObject = Cast<UAssetObject>(Object))
		{
			const TSharedRef<FMyAssetEditorToolkit> RecoilAssetEditorToolkit = MakeShareable(new FMyAssetEditorToolkit());
			RecoilAssetEditorToolkit->InitializeAssetEditor(ToolKitModeType, EditWithinLevelEditor, AssetObject);
		}
	}
}

uint32 FAssetTypeAction_MyAsset::GetCategories()
{
	return MyAssetCategory;
}
