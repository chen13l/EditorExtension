// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetFactory.h"

#include "AssetObject.h"

UAssetFactory::UAssetFactory()
{
	SupportedClass = UAssetObject::StaticClass();
	bCreateNew = true;
}

bool UAssetFactory::CanCreateNew() const
{
	return true;
}

bool UAssetFactory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context,
                                         FFeedbackContext* Warn, FName CallingContext)
{
	return NewObject<UAssetObject>(InParent, InClass, InName, Flags);
}
