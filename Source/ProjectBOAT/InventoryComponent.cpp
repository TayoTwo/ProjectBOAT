// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Weapon.h"

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

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Display, TEXT("ITEM COUNT %d"),items.Num());
	// ...
}

void UInventoryComponent::AddItem(FItem item){

	UE_LOG(LogTemp, Display, TEXT("ADDING %s to %s"),*item.itemName,*GetOwner()->GetName());
	items.Add(item);

}

void UInventoryComponent::AddItem(AWeapon* weaponActor)
{

	FItem weaponItem = {*weaponActor->GetName(),
						true,
						weaponActor
						};
	AddItem(weaponItem);

}

void UInventoryComponent::RemoveItem(FItem item){

	//items.Remove(item);
	//items->RemoveSingle(item);
	//items->Remove(item);

}