// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShip.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.h"

// Sets default values
ABaseShip::ABaseShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	weaponSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Spawn Point"));
	weaponSpawnPoint->SetupAttachment(CapsuleComp);

}

void ABaseShip::BeginPlay(){

	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("BEGIN PLAY STARTING"));

    if(!weaponActor){

        weaponActor = GetWorld()->SpawnActor<AWeapon>(currentWeapon,weaponSpawnPoint->GetComponentLocation(),weaponSpawnPoint->GetComponentRotation());

        weaponActor->AttachToActor(this,FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));

        weaponActor->SetActorLocation(weaponSpawnPoint->GetComponentLocation());

    }

}

void ABaseShip::TurnWeapon(FVector targetLocation){

	if(weaponActor){

		FVector targetDir = targetLocation - weaponActor->GetActorLocation();
		FRotator lookAtRotation = FRotator(0.f,targetDir.Rotation().Yaw,0.f);

		weaponActor->SetActorRotation(
								FMath::RInterpTo(weaponActor->GetActorRotation(),
								lookAtRotation,
								UGameplayStatics::GetWorldDeltaSeconds(this),
								25.f));

	}

}

void ABaseShip::Fire(){

	UE_LOG(LogTemp, Display, TEXT("FIRE!"));
	
	if(weaponActor){

		FVector projectileSpawnLocation = weaponActor->ProjectileSpawnPoint->GetComponentLocation();
		FRotator projectileSpawnRotation = weaponActor->ProjectileSpawnPoint->GetComponentRotation();
		FString locationString = projectileSpawnLocation.ToString();

		GetWorld()->SpawnActor<AProjectile>(weaponActor->WeaponProjectile,projectileSpawnLocation,projectileSpawnRotation);

	} else {

		UE_LOG(LogTemp, Display, TEXT("Spawnpoint not set!"));

	}

}

