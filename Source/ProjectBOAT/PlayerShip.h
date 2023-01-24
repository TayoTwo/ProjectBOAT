// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "PlayerShip.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOAT_API APlayerShip : public ABaseShip
{
	GENERATED_BODY()

public:
	APlayerShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void Fire() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveVertical(float value);
	void MoveHorizontal(float value);
	void SetTarget();
	void MoveToTarget();

	UPROPERTY(EditAnywhere)
	float keepDriftingDistance = 100.f;
	bool bIsDrifting = false;
	
	APlayerController* PlayerController;

private:

	UPROPERTY(EditAnywhere,Category = "Components")
	class USpringArmComponent* springArm;
	UPROPERTY(EditAnywhere,Category = "Components")
	class UCameraComponent* camera;

	
};
