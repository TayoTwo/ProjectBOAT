// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "BaseShip.h"

void UWeaponItem::Use(ABaseShip* ship){

    Super::Use(ship);

    ship->UseItem(this);

}