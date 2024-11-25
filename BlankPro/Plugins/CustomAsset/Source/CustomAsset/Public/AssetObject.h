// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AssetObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CUSTOMASSET_API UAssetObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="My Asset")
	FName AssetName;
	
};
