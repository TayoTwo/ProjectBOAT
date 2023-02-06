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
	EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory); 
	class ABaseShip* ship;
	virtual void OnGameplayTaskActivated(UGameplayTask &Task) override;
	void MoveToTarget();

protected:

	
};
