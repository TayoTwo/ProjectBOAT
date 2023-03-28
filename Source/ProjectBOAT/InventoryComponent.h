// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

//DELEGATE FOR UI BLUEPRINTS
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBOAT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// UFUNCTION(BlueprintCallable)
	// void InitInventory(UItem &item);
	UFUNCTION(BlueprintCallable)
	bool AddItem(UItem* item);
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UItem* item);

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Items")
	TArray<class UItem*> inventoryItems;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Items")
	int32 maxInventorySize = 10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Items")
	int gold;


};
