// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTShootTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOAT_API UBTTShootTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTShootTarget(const FObjectInitializer &ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds) override; 
	virtual void OnTaskFinished(UBehaviorTreeComponent & OwnerComp,uint8 * NodeMemory,EBTNodeResult::Type TaskResult); 
	class ABaseShip* ship;
	class APirateAIController* controller;
	class AWeapon* weaponActor;
	UPROPERTY(EditAnywhere)
	float AcceptableRadius;
	UPROPERTY(VisibleAnywhere)
	bool bHasTaskFinished;
	virtual void OnGameplayTaskActivated(UGameplayTask &Task) override;
	
};
