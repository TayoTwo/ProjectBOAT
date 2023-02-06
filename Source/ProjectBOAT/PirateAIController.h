 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "AIController.h"
#include "PirateAIController.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTBOAT_API APirateAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void SetupController();

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;
	UPROPERTY(EditAnywhere)
	ABaseShip* ship;

};
