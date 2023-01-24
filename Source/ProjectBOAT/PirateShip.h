// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
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

	void SetTarget();
	void MoveToTarget();

	class APlayerShip* playerShip;

	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Pirate Stats")
	float aggroRange;
	UPROPERTY(EditAnywhere, Category = "Pirate Stats")
	float shootRange;
	void CheckFireCondition();
	bool CanFire();
	
};
