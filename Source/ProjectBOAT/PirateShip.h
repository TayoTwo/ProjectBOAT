// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "PirateShip.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTBOAT_API APirateShip : public ABaseShip
{
	GENERATED_BODY()

public:

	APirateShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void Fire() override;
	virtual void Die() override;

	void SetTarget();

	class APawn* playerShip;
	class APirateAIController* controller;

	void CheckFireCondition();
	bool CanFire();

private:

	// class UAIPerceptionComponent* PerceptionComponent;
	// class UAISenseConfig_Sight* sightConfig;

	// UFUNCTION()	
	// void OnSightSensed(const TArray<AActor*>&DetectedPawn);
	
};
