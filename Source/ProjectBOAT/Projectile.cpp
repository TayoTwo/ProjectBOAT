// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "PlayerShip.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	//projectileMovementComponent->SetAttachement(RootComponent);

	projectileMovementComponent->InitialSpeed = initialSpeed;
	projectileMovementComponent->MaxSpeed = maxSpeed;
	projectileMovementComponent->bIsHomingProjectile = hasTracking;
	projectileMovementComponent->HomingAccelerationMagnitude = TrackingStrength;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(MyOwner){

		MyOwner = GetOwner();

	} else {

		return;

	}


	if(Cast<APlayerShip>(MyOwner)->PlayerController && hasTracking){

		//projectileMovementComponent->HomingTargetComponent = Cast<ABaseShip>(MyOwner)->EnemyTarget;

		//projectileMovementComponent->ComputeHomingAcceleration()

        // FVector targetDir = targetPosition - GetActorLocation();
        // targetDir.Z = 0;
        // FRotator targetRotation = targetDir.ToOrientationRotator();

		// targetDir = targetPosition - GetActorLocation();
		// FRotator lookAtRotation = FRotator(0.f,targetDir.Rotation().Yaw,0.f);

		// SetActorRotation(
		// 				FMath::RInterpTo(GetActorRotation(),
		// 				lookAtRotation,
		// 				UGameplayStatics::GetWorldDeltaSeconds(this),
		// 				TrackingStrength)
		// 				);
						
		//         DrawDebugSphere(GetWorld(),
        //                 hitResult.ImpactPoint,
        //                 25.f,
        //                 12,
        //                 FColor::Red,
        //                 false,
        //                 3.f);

	}

}

