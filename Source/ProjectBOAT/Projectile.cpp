// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "PlayerShip.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));
	RootComponent = sphereComponent;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	projectileMesh->SetupAttachment(sphereComponent);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	projectileMovementComponent->InitialSpeed = initialSpeed;
	projectileMovementComponent->MaxSpeed = maxSpeed;
	projectileMovementComponent->bIsHomingProjectile = hasTracking;
	projectileMovementComponent->HomingAccelerationMagnitude = TrackingStrength;

	SmokeTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrail->SetupAttachment(projectileMesh);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	sphereComponent->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetOwner() && Cast<APlayerShip>(GetOwner())->PlayerController && hasTracking){

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

void AProjectile::OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit){

	//UE_LOG(LogTemp, Display, TEXT("HIT %s"),*OtherActor->GetName());
	auto MyOwner = GetOwner();

	if(MyOwner == nullptr) return;

	//UE_LOG(LogTemp, Display, TEXT("HAS OWNER"));

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor != MyOwner){

		if(OtherActor && OtherActor != this){

			//UE_LOG(LogTemp, Display, TEXT("APPLYING DMG"));
			UGameplayStatics::ApplyDamage(OtherActor,Damage, MyOwnerInstigator, this,DamageTypeClass);
			UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());
			UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());

		}

		Destroy();

	}

	//UE_LOG(LogTemp,Warning, TEXT("%s hit %s's %s"),*HitComp->GetName(),*OtherActor->GetName(),*OtherComp->GetName());

}

