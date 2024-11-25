#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class CUSTOMASSET_API FAssetTypeAction_MyAsset : public FAssetTypeActions_Base
{
public:
	FAssetTypeAction_MyAsset(EAssetTypeCategories::Type Category);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, const EAssetTypeActivationOpenedMethod OpenedMethod,
	                             TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
