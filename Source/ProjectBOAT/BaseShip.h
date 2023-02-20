// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "Dropbox.h"
#include "InventoryComponent.h"
#include "HealthComponent.h"
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
	void TurnWeapon(FVector targetLocation);
	UPROPERTY(EditAnywhere,Category = "Stats")
	float turretTurnSpeed = 25.f;
	UPROPERTY(EditAnywhere,Category = "Stats")
	float moveSpeed = 500;
	UPROPERTY(EditAnywhere,Category = "Stats")
	float turnSpeed = 500;

	UPROPERTY(EditAnywhere)
	class AWeapon* weaponActor;
	class AActor* EnemyTarget;

	UPROPERTY(EditAnywhere)
	class USceneComponent* weaponSpawnPoint;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	virtual void Fire();
	virtual void Die();
	class AActor* targetActor;
	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADropbox> dropbox;
	UPROPERTY(EditAnywhere)
	class UInventoryComponent* inventoryComponent;
	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class TSubclassOf<class AWeapon> currentWeapon;

	UPROPERTY(VisibleAnywhere,Category = "MoveTo")
	bool isMovingToTarget = false;
	UPROPERTY(VisibleAnywhere,Category = "MoveTo")
	FVector targetPosition;
	UPROPERTY(VisibleAnywhere,Category = "MoveTo")
	FRotator targetRotation;

private:

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	class UHealthComponent* healthComponent;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit);

	// UPROPERTY(EditAnywhere,Category = "Combat")
	// TSubclassOf<class AProjectile> ProjectileClass;

};