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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	float FireRate = 25.f;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> WeaponProjectile;

	UPROPERTY(EditAnywhere)
	class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	class ABaseShip* ownerShip;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};