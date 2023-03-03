// Fill out your copyright notice in the Description page of Project Settings.


#include "DangerZone.h"
#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADangerZone::ADangerZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADangerZone::SpawnPirates(){

	UE_LOG(LogTemp, Display, TEXT("SPAWNING PIRATES "));
	
	for(int i = 0;i < spawnCount;i++){

		FVector spawnPos = FVector(FMath::RandRange(-spawnRadius, spawnRadius),FMath::RandRange(-spawnRadius, spawnRadius),0); 
		FRotator spawnRot = FRotator(0,FMath::RandRange(0,360),0);
		GetWorld()->SpawnActor<APirateShip>(pirate,spawnPos,spawnRot);

	}

	bSpawnedPirates = true;

}

// Called when the game starts or when spawned
void ADangerZone::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(this,0));

	//SpawnPirates();
	
}

// Called every frame
void ADangerZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player != nullptr) {

		float distance = FVector::Distance(player->GetActorLocation(), GetActorLocation());

		if (distance <= spawnRadius && !bSpawnedPirates) {

			SpawnPirates();

		}

	} else {

		//UE_LOG(LogTemp, Display, TEXT("CASTING PLAYER IN TICK"));
		player = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(this, 0));

	}

	DrawDebugSphere(GetWorld(),
                    GetActorLocation(),
                    spawnRadius,
                    12,
                    FColor::Red,
                    false,
                    -1.f);

}

