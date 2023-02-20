// Fill out your copyright notice in the Description page of Project Settings.


#include "DangerZone.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADangerZone::ADangerZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADangerZone::SpawnPirate(){

	FVector spawnPos = FVector(FMath::RandRange(-spawnRadius, spawnRadius),FMath::RandRange(-spawnRadius, spawnRadius),0); 
	FRotator spawnRot = FRotator(0,FMath::RandRange(0,360),0);
	GetWorld()->SpawnActor<APirateShip>(pirate,spawnPos,spawnRot);

}

// Called when the game starts or when spawned
void ADangerZone::BeginPlay()
{
	Super::BeginPlay();

	if(pirate != nullptr){

		//GetWorldTimerManager().SetTimer(spawnTimerHandler,this, &ADangerZone::SpawnPirate,weaponActor->FireRate,true);

	}

	for(int i = 0;i < spawnCount;i++){

		SpawnPirate();

	}
	
}

// Called every frame
void ADangerZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(),
                    GetActorLocation(),
                    spawnRadius,
                    12,
                    FColor::Red,
                    false,
                    -1.f);

}

