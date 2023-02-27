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
    Patroling       UMETA(DisplayName="Patroling"),
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
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<class APatrolRoute> patrolRoute;
	class APatrolRoute* patrolRouteActor;

	UPROPERTY(EditAnywhere, Category = "AI")
	float aggroRange;
	UPROPERTY(EditAnywhere, Category = "AI")
	float shootRange;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void SetupController();

private:
	UPROPERTY(VisibleAnywhere)
	class UBehaviorTree* AIBehaviorTree;

	class UAIPerceptionComponent* PerceptionComponent;
	class UAISenseConfig_Sight* sightConfig;

	UFUNCTION()	
	void OnSightSensed(const TArray<AActor*>&DetectedPawn);

};

