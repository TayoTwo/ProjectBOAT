// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Weapon.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

	inventoryItems = TArray<UItem*>();
	maxInventorySize = 10;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

// void UInventoryComponent::InitInventory(UItem &item){


// 	inventoryItems = TArray<UItem*>();

	
// }

//DEBUGGING NOTES
//ITS SOMETHING TO DO WITH TARRAY
//Checklist:
//static_cast didn't work
//I tried using TMaps instead so its definitely something to do with the Item class


bool UInventoryComponent::AddItem(UItem* item){
 
	//UE_LOG(LogTemp, Display, TEXT("INVENTORY SIZE: %d"),items.Num());
	//UE_LOG(LogTemp, Display, TEXT("MAX INVENTORY SIZE IS %d"),maxInventorySize);

	if(inventoryItems.Num() >= maxInventorySize || !item){

		UE_LOG(LogTemp, Display, TEXT("INVENTORY IS FULL OR ITEM IS NULL"));
		return false;

	}

	UE_LOG(LogTemp, Display, TEXT("ADDING %s to %s"), 
	*item->GetName(), 
	*GetOwner()->GetName());

	item->ownerInventory  = this;
	item->World = GetWorld();
	inventoryItems.Add(item);

	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(UItem* item){

	if(item){

		item->ownerInventory = nullptr;
		item->World = nullptr;
		inventoryItems.RemoveSingle(item);
		OnInventoryUpdated.Broadcast();
		return true;

	}

	return false;

}