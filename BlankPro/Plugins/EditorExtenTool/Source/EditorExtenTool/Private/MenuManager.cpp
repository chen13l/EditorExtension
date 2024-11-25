// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuManager.h"

#include "LevelEditor.h"

void UMenuManager::Initialize(FSubsystemCollectionBase& Collection)
{
	//把所有需要绑定的类都继承一个基类(UMenuItem)，最后用迭代器遍历的时候对UClass进行判断就可以找到所有需要绑定委托的类了
	// 构造NodeList
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* CurrentClass = *It;
		if (CurrentClass->IsChildOf(UMenuItem::StaticClass())
			&& !(CurrentClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			AddMenuItemToNodeList(Cast<UMenuItem>(CurrentClass->GetDefaultObject()));
		}
	}

	//LevelEditor模块负责的就是打开UE4编辑器首先映入眼帘的各个编辑窗口。其中包括菜单栏、工具栏、视窗、详情面板、Modes面板、世界大纲面板等GUI功能。
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	/*
	 *  FName ExtensionHook。要挂在哪个菜单附近。
	 *  EExtensionHook::Position HookPosition。要挂的位置的类型，前或后
	 *  const TSharedPtr< FUICommandList >& CommandList。可以用于绑定通用的按钮操作，比如复制粘贴撤销等。可以参考FCurveEditor类对CommandList的使用。
	 *  MenuBarExtensionDelegate。菜单栏扩展委托。CreateUObject不是创建UObject的意思，而是CreateByUObjet
	 */
	MenuExtender->AddMenuBarExtension("Help",
	                                  EExtensionHook::After,
	                                  nullptr,
	                                  FMenuBarExtensionDelegate::CreateUObject(this, &UMenuManager::AddMenuBarExtension));
	// 添加拓展项到关卡编辑器
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void UMenuManager::Deinitialize()
{
	Super::Deinitialize();
}

static void AddMenuExtension(FMenuBuilder& Builder, TArray<FMenuItemNode>* NodeList)
{
	for (int i = 0; i < NodeList->Num(); ++i)
	{
		FMenuItemNode& Node = (*NodeList)[i];
		// 对于根节点以外的节点则需要判断是叶子节点还是父节点。是叶子节点则调用MenuEntry注册委托。
		if (Node.MenuItem != nullptr) // 有MenuItem为叶子节点
		{
			Builder.AddMenuEntry(
				FText::FromString(Node.MenuItem->GetMenuName()),
				FText::FromString(Node.MenuItem->GetMenuToolTip()),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateUObject(Node.MenuItem, &UMenuItem::OnMenuClick)));
		}
		else if (!Node.NodeName.IsEmpty() && Node.Children.Num() > 0) // 没有则为父节点，递归调用自己
		{
			Builder.AddSubMenu(
				FText::FromString(Node.NodeName),
				FText::FromString(TEXT("")),
				FNewMenuDelegate::CreateStatic(&AddMenuExtension, &Node.Children));
		}
	}
}

void UMenuManager::AddMenuBarExtension(FMenuBarBuilder& Builder)
{
	for (FMenuItemNode& Node : RootNodeList)
	{
		// 对于根节点，调用AddPullDownMenu
		if (!Node.NodeName.IsEmpty() && Node.Children.Num() > 0)
		{
			Builder.AddPullDownMenu(
				FText::FromString(Node.NodeName),
				FText::FromString(TEXT("")),
				FNewMenuDelegate::CreateStatic(&AddMenuExtension, &Node.Children));
		}
	}
}

//查找节点
static FMenuItemNode* FindmenuItemNode(TArray<FMenuItemNode>& MenuNodes, const FString& MenuName)
{
	for (FMenuItemNode& Node : MenuNodes)
	{
		if (Node.NodeName == MenuName) { return &Node; }
	}

	return nullptr;
}

void UMenuManager::AddMenuItemToNodeList(UMenuItem* MenuItem)
{
	if (MenuItem == nullptr) { return; }

	TArray<FString> MenuNames;
	FString Path = MenuItem->GetMenuPath();
	if (Path.IsEmpty()) { return; }

	//将路径上各节点名称按顺序存储
	FString Left;
	while (Path.Split("/", &Left, &Path))
	{
		if (Left.IsEmpty()) { continue; }
		MenuNames.Add(Left);
	}
	MenuNames.Add(Path);

	// 查找目标节点根节点，没有则创建
	FMenuItemNode* RootMenuNode = FindmenuItemNode(RootNodeList, MenuNames[0]);
	if (RootMenuNode == nullptr)
	{
		FMenuItemNode MenuItemNode;
		MenuItemNode.NodeName = MenuNames[0];
		int32 Index = RootNodeList.Add(MenuItemNode);
		RootMenuNode = &RootNodeList[Index];
	}

	// 根据上面记录的字符串数组循环查找，没有则创建节点
	FMenuItemNode* ParentNode = RootMenuNode;
	for (int i = 1; i < MenuNames.Num(); ++i)
	{
		FString& ChildName = MenuNames[i];
		FMenuItemNode* ChildNode = FindmenuItemNode(ParentNode->Children, ChildName);
		if (ChildNode == nullptr)
		{
			FMenuItemNode MenuItemNode;
			MenuItemNode.NodeName = ChildName;
			int32 Index = ParentNode->Children.Add(MenuItemNode);
			ChildNode = &ParentNode->Children[Index];
		}
		ParentNode = ChildNode;
	}

	// 给叶子节点赋值MenuItem的指针
	ParentNode->MenuItem = MenuItem;
}
