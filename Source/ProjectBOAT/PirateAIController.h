 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "PirateAIController.generated.h"

UENUM(BlueprintType)
enum class EPirateState : uint8 {
    Passive       UMETA(DisplayName="Passive"),
    Chasing       UMETA(DisplayName="Chasing"),
    Attacking     UMETA(DisplayName="Attacking")
};

/**
 * 
 */
UCLASS()
class PROJECTBOAT_API APirateAIController : public AAIController
{
	GENERATED_BODY()

public:
	APirateAIController();
	UPROPERTY(EditAnywhere)
	ABaseShip* ship;
	APawn* TargetPawn;
	UPROPERTY(EditAnywhere, Category = "Pirate Stats")
	float aggroRange;
	UPROPERTY(EditAnywhere, Category = "Pirate Stats")
	float shootRange;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void SetupController();

private:
	UPROPERTY(VisibleAnywhere)
	class UBehaviorTree* AIBehaviorTree;
	// UPROPERTY(EditAnywhere)
	// EPirateState currentState;
	// UAIPerceptionComponent PerceptionComponent;
	// UAISenseConfig_Sight sightConfig;

	// void OnSightSensed();

};

