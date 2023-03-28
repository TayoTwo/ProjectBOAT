// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOAT_API UWeaponItem : public UItem
{
	GENERATED_BODY()

public:

	virtual void Use(class ABaseShip* ship) override;
	
};
