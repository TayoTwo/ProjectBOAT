// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "BaseShip.h"

UItem::UItem(){



}

void UItem::Use(ABaseShip* ship){



}

FString UItem::GetName(){

    return itemDisplayName.ToString();

}