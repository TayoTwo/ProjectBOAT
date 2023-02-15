// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

/**
 * 
 */

USTRUCT()
struct FItem {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString itemName;
	UPROPERTY(EditAnywhere)
	bool bIsWeapon;
	UPROPERTY(EditAnywhere)
	AWeapon* Weapon;

};

UCLASS()
class PROJECTBOAT_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Items")
	TArray<FItem> items;
	
};
