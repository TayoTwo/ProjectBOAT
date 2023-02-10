// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTMoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOAT_API UBTTMoveToTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public: 

	UBTTMoveToTarget(const FObjectInitializer &ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds) override; 
	class ABaseShip* ship;
	class APirateAIController* controller;
	UPROPERTY(EditAnywhere)
	float AcceptableRadius;
	UPROPERTY(VisibleAnywhere)
	bool bHasTaskFinished;
	virtual void OnGameplayTaskActivated(UGameplayTask &Task) override;

protected:

	
};
