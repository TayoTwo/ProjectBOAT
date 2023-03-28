// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "Item.h"
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
	void ChangeFireState();
	virtual void Die() override;
	void EquipItem(UItem* item);


	void SetTarget();
	void MoveToTarget();

	UPROPERTY(EditAnywhere)
	float keepDriftingDistance = 100.f;
	bool bIsDrifting = false;
	FVector spawnPos;
	FTimerHandle timerHandle;
	bool canFire;
	
	APlayerController* PlayerController;

private:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveVertical(float value);
	void MoveHorizontal(float value);
	void StopMovement();
	void ShowInventory();

	UPROPERTY(EditDefaultsOnly,Category = "Components")
	class USpringArmComponent* springArm;
	UPROPERTY(EditDefaultsOnly,Category = "Components")
	class UCameraComponent* camera;
	//UPROPERTY(EditDefaultsOnly,Category = "UI")
	//TSubclassOf<class UUserWidget> inventoryWidget;

	
};