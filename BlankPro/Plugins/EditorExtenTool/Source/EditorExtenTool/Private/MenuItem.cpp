// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuItem.h"

FString& UMenuItem::GetMenuPath()
{
	return MenuPath;
}

FString& UMenuItem::GetMenuName()
{
	return MenuName;
}

FString& UMenuItem::GetMenuToolTip()
{
	return MenuToolTip;
}

void UMenuItem::InitMenu(const FString& Path, const FString& Tooltip)
{
	MenuPath = Path;
	MenuToolTip = Tooltip;
	MenuName = FPaths::GetPathLeaf(Path);
}
