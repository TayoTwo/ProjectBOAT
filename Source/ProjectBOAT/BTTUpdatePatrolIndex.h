// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PirateAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTUpdatePatrolIndex.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOAT_API UBTTUpdatePatrolIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds) override; 
	APirateAIController* controller;
	
	UPROPERTY(EditAnywhere)
	float AcceptableRadius;
	UPROPERTY(VisibleAnywhere)
	bool bHasTaskFinished;
	virtual void OnGameplayTaskActivated(UGameplayTask &Task) override;

};
