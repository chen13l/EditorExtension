#include "AssetEditor/MyAssetEditorToolkit.h"

// 在注册函数与注销函数中处理Detail面板
void FMyAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("Asset Editor"));
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	InTabManager->RegisterTabSpawner(FName("MyAssetPropertyTab"),
	                                 FOnSpawnTab::CreateRaw(this, &FMyAssetEditorToolkit::SpawnDetailTab))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner(FName("MyAssetGraphEditorTab"), FOnSpawnTab::CreateLambda(
		                                 [&](const FSpawnTabArgs& SpawnTabArgs)
		                                 {
			                                 return SNew(SDockTab)
				                                 [
					                                 SNew(SGraphEditor).GraphToEdit(EdGraph)
				                                 ];
		                                 }))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FMyAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(PropertyEditorTabName);
	InTabManager->UnregisterTabSpawner(GraphEditorTabName);
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

void FMyAssetEditorToolkit::InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets)
{
	//要编辑一个可以被持久化存储的图，图应该存在自定义资产中，随自定义产的创建初始化。
	EdGraph = NewObject<UEdGraph>();
	EdGraph->Schema = UEdGraphSchema::StaticClass();
	EdGraph->AddToRoot();

	const TSharedRef<FTabManager::FLayout> StandaloneMyAssetEditor = FTabManager::NewLayout("MyAssetEditor")->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)->Split(
			FTabManager::NewStack()->AddTab(GraphEditorTabName, ETabState::OpenedTab)));

	InitAssetEditor(Mode, InitToolkitHost, FName("OurAssetEditor"), StandaloneMyAssetEditor, true, true, InAssets);
	RegenerateMenusAndToolbars();
}

TSharedRef<SDockTab> FMyAssetEditorToolkit::SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs) const
{
	//加载属性编辑器模块
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;
	//创建属性编辑器的Slate
	const TSharedRef<IDetailsView> AssetPropertyView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	//将对象传入，这样就是自动生成对象的属性面板
	AssetPropertyView->SetObject(GetEditingObject());
	return SNew(SDockTab)
		[
			AssetPropertyView
		];
}
