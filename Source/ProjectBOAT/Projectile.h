// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class PROJECTBOAT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Projectile Stats")
	float initialSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Projectile Stats")
	float maxSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* projectileMovementComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
