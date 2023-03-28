// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemType : uint8{

	SAIL,
	HULL,
	WEAPON

};

UCLASS(Abstract,BlueprintType,Blueprintable,EditInlineNew,DefaultToInstanced)
class PROJECTBOAT_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();

	virtual class UWorld* GetWorld() const {return World;};

	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info")
	FText ActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info")
	FText itemDisplayName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info", meta = (MultiLine = true))
	FText itemDescription;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	EItemType itemType;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	UStaticMesh* mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	TSubclassOf<class AWeapon> weaponClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Info")
	AWeapon* itemWeaponActor;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float HP;	

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Weight;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float value;


	UPROPERTY()	
	class UInventoryComponent* ownerInventory;

	FString GetName();

	virtual void Use(class ABaseShip* ship);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(ABaseShip* ship); 

};
