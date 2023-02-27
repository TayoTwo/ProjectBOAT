// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShip.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Weapon.h"
#include "Target.h"

// Sets default values
ABaseShip::ABaseShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision Component"));
	RootComponent = boxComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(boxComponent);

	weaponSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Spawn Point"));
	weaponSpawnPoint->SetupAttachment(boxComponent);

	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void ABaseShip::BeginPlay(){

	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("BEGIN PLAY STARTING"));

    if(!weaponActor){

		//UE_LOG(LogTemp, Display, TEXT("SPAWNING WEAPON"));

        weaponActor = GetWorld()->SpawnActor<AWeapon>(currentWeapon,weaponSpawnPoint->GetComponentLocation(),weaponSpawnPoint->GetComponentRotation());

        weaponActor->AttachToActor(this,FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));

        weaponActor->SetActorLocation(weaponSpawnPoint->GetComponentLocation());

		inventoryComponent->AddItem(Cast<UItem>(weaponActor->itemClass));

    }

	
	//UE_LOG(LogTemp, Display, TEXT("TEST"));

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

	//UE_LOG(LogTemp, Display, TEXT("FIRE!"));
	
	if(weaponActor){

		FVector projectileSpawnLocation = weaponActor->ProjectileSpawnPoint->GetComponentLocation();
		FRotator projectileSpawnRotation = weaponActor->ProjectileSpawnPoint->GetComponentRotation();
		FString locationString = projectileSpawnLocation.ToString();

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(weaponActor->WeaponProjectile,projectileSpawnLocation,projectileSpawnRotation);
		Projectile->SetOwner(this);

	} else {

		UE_LOG(LogTemp, Display, TEXT("Spawnpoint not set!"));

	}

}

void ABaseShip::Die(){

	UE_LOG(LogTemp, Display, TEXT("%s has DIED"),*GetName());

}
void ABaseShip::OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit){

	UE_LOG(LogTemp, Display, TEXT("HIT SOMETHING"));

}