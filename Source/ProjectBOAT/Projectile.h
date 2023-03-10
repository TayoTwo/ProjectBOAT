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
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Projectile Stats")
	float initialSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Projectile Stats")
	float maxSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Projectile Stats")
	bool hasTracking = false;
	
	UPROPERTY(EditAnywhere, Category = "Projectile Stats")
	float TrackingStrength = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* sphereComponent;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* projectileMovementComponent;
	
	UPROPERTY(EditAnywhere, Category = "VFX")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "VFX")
	class UParticleSystemComponent* SmokeTrail;

	UPROPERTY(EditAnywhere, Category = "SFX")
	class USoundBase* LaunchSound;
	
	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundBase* HitSound;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//class AActor* MyOwner;

};
