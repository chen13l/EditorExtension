// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MenuItem.generated.h"

/**
 * 
 */
UCLASS()
class EDITOREXTENTOOL_API UMenuItem : public UObject
{
public:
	FString& GetMenuPath();
	FString& GetMenuName();
	FString& GetMenuToolTip();

private:
	GENERATED_BODY()

public:
	virtual ~UMenuItem() {};
	virtual void OnMenuClick() {};

private:
	FString MenuPath; //路径，"/A/B/C/D"
	FString MenuName; //名称，"D"
 	FString MenuToolTip; //菜单提示

protected:
	void InitMenu(const FString& Path,const FString& Tooltip);
};
