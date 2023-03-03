// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PirateShip.h"
#include "PlayerShip.h"
#include "GameFramework/Actor.h"
#include "DangerZone.generated.h"

UCLASS()
class PROJECTBOAT_API ADangerZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADangerZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	APlayerShip* player;
	void SpawnPirates();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APirateShip> pirate;
	UPROPERTY(EditAnywhere)
	float spawnRadius;
	UPROPERTY(EditAnywhere)
	float spawnCount;
	bool bSpawnedPirates;
	//FTimerHandle spawnTimerHandler;

};
