// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuItem.h"
#include "Subsystems/EngineSubsystem.h"
#include "MenuManager.generated.h"

struct FMenuItemNode
{
	FString NodeName;
	UMenuItem* MenuItem = nullptr;
	TArray<FMenuItemNode> Children;
};

/**
 * 
 */
UCLASS()
class EDITOREXTENTOOL_API UMenuManager : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	TArray<FMenuItemNode> RootNodeList;

	void AddMenuBarExtension(FMenuBarBuilder& Builder);
	// 根据MenuItem的CDO构建NodeList
	void AddMenuItemToNodeList(UMenuItem* MenuItem);
	
};


