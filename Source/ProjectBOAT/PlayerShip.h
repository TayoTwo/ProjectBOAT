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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveVertical(float value);
	void MoveHorizontal(float value);
	void SetTarget();
	void MoveToTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere,Category = "Stats")
	float moveSpeed = 500;
	UPROPERTY(EditAnywhere,Category = "Stats")
	float turnSpeed = 500;
	UPROPERTY(EditAnywhere,Category = "MoveTo")
	float toTargetDistance = 100;
	UPROPERTY(VisibleAnywhere,Category = "MoveTo")
	bool isMovingToTarget = false;
	UPROPERTY(VisibleAnywhere,Category = "MoveTo")
	FVector targetPosition;
	UPROPERTY(EditAnywhere,Category = "Components")
	class USpringArmComponent* springArm;
	UPROPERTY(EditAnywhere,Category = "Components")
	class UCameraComponent* camera;

	APlayerController* PlayerController;
	
};
