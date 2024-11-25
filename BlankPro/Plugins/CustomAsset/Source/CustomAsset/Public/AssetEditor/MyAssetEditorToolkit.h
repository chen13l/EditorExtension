#pragma once

class FMyAssetEditorToolkit : public FAssetEditorToolkit
{
public:
	/** IToolkit interface */
	virtual FName GetToolkitFName() const override { return "SimpleAssetEditor"; };
	virtual FText GetBaseToolkitName() const override { return INVTEXT("Simple Asset Editor"); };
	virtual FString GetWorldCentricTabPrefix() const override { return "Simple Asset "; };
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; };
	/** End IToolkit interface */

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

public:
	void InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets);

private:
	// 生成细节面板
	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs) const;
	//如果要编辑一个可以被持久化存储的图，图应该存在自定义资产中，随自定义产的创建初始化。
	TObjectPtr<UEdGraph> EdGraph;

	inline static const FName GraphEditorTabName {"MyAssetsGraphEditor"};
	inline static const FName PropertyEditorTabName {"MyAssetsPropertyEditor"};
};
