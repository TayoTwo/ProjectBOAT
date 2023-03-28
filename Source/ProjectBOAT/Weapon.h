// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROJECTBOAT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(Instanced,EditAnywhere,BlueprintReadWrite)
	class UItem* itemClass;
	//UItem* GetItemClass();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> WeaponProjectile;
	
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	float FireRate = 2.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	class ABaseShip* ownerShip;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
