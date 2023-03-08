// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Weapon.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	maxInventorySize = 10;
	
}

bool UInventoryComponent::AddItem(UItem* item){

	
	if(items.Num() >= maxInventorySize || item == nullptr){

		UE_LOG(LogTemp, Display, TEXT("ITEM IS NULL"));
		return false;

	}

	UE_LOG(LogTemp, Display, TEXT("ADDING %s to %s"), *item->itemDisplayName.ToString(), *GetOwner()->GetName());

	item->ownerInventory  = this;
	item->World = GetWorld();
	items.Add(item);
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(UItem* item){

	if(item){

		item->ownerInventory = nullptr;
		item->World = nullptr;
		items.RemoveSingle(item);
		OnInventoryUpdated.Broadcast();
		return true;

	}

	return false;

}