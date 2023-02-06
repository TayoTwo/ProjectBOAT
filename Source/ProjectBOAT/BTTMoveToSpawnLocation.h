// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTMoveToSpawnLocation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOAT_API UBTTMoveToSpawnLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public: 

	UBTTMoveToSpawnLocation(const FObjectInitializer &ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) override; 
	virtual void TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds) override; 
	class ABaseShip* ship;
	virtual void OnGameplayTaskActivated(UGameplayTask &Task) override;

protected:
	
};
