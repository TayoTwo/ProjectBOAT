// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseShip.generated.h"

UCLASS()
class PROJECTBOAT_API ABaseShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseShip();
	UPROPERTY(EditAnywhere,Category = "Stats")
	float turretTurnSpeed = 25.f;

protected:

	void TurnWeapon(FVector targetLocation);
	void Fire();

	UPROPERTY(EditAnywhere)
	class TSubclassOf<class AWeapon> currentWeapon;

private:

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BaseMesh;

	// UPROPERTY(EditAnywhere,Category = "Combat")
	// TSubclassOf<class AProjectile> ProjectileClass;

};