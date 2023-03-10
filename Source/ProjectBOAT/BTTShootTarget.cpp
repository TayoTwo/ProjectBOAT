// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTShootTarget.h"
#include "PirateAIController.h"
#include "Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PirateShip.h"

UBTTShootTarget::UBTTShootTarget(const FObjectInitializer &ObjectInitializer){


}

EBTNodeResult::Type UBTTShootTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory){

    Super::ExecuteTask(OwnerComp,NodeMemory);

    //UE_LOG(LogTemp, Display, TEXT("TASK EXECUTING"));
    bNotifyTick = true;
    controller = Cast<APirateAIController>(OwnerComp.GetAIOwner());
    ship = controller->ship;
    weaponActor = controller->ship->weaponActor;

    if(weaponActor){

        ship->GetWorldTimerManager().SetTimer(ship->FireRateTimerHandle,ship, &ABaseShip::Fire,weaponActor->FireRate,true);
        //ship->Fire();

    }

    return EBTNodeResult::Type::InProgress;

}

void UBTTShootTarget::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds){

    Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);

    if(ship != nullptr){

        UBlackboardComponent* blackBoard = controller->GetBlackboardComponent(); 
        FVector targetPosition = blackBoard->GetValueAsVector("ShootTarget");
        float distance = FVector::Distance(ship->GetActorLocation(),targetPosition);

        ship->TurnWeapon(targetPosition);
        //ship->GetWorldTimerManager().SetTimer(ship->FireRateTimerHandle,ship, &ABaseShip::Fire,weaponActor->FireRate,true);

        if(distance >= controller->shootRange){

            //ship->GetWorldTimerManager().ClearTimer(ship->FireRateTimerHandle);

            //UE_LOG(LogTemp, Display, TEXT("SHOOT ABORTED"));
            FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);

        }

    }

}

void UBTTShootTarget::OnTaskFinished(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, EBTNodeResult::Type TaskResult){

    Super::OnTaskFinished(OwnerComp,NodeMemory,TaskResult);

    // UE_LOG(LogTemp, Display, TEXT("TASK FINISHED"));

    if(ship != nullptr){

        ship->GetWorldTimerManager().ClearTimer(ship->FireRateTimerHandle);

    }

}

void UBTTShootTarget::OnGameplayTaskActivated(UGameplayTask &Task){

    Super::OnGameplayTaskActivated(Task);

    if(ship != nullptr){

        ship->GetWorldTimerManager().ClearTimer(ship->FireRateTimerHandle);

    }

}

void UBTTShootTarget::OnGameplayTaskDeactivated(UGameplayTask &Task){

    Super::OnGameplayTaskDeactivated(Task);

    // UE_LOG(LogTemp, Display, TEXT("TASK FINISHED"));

    if(ship != nullptr){

        ship->GetWorldTimerManager().ClearTimer(ship->FireRateTimerHandle);

    }

}

EBTNodeResult::Type UBTTShootTarget::AbortTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory){

    Super::AbortTask(OwnerComp,NodeMemory);

    UE_LOG(LogTemp, Display, TEXT("TASK ABORTED"));

    if(ship != nullptr){

        ship->GetWorldTimerManager().ClearTimer(ship->FireRateTimerHandle);

    }

    return EBTNodeResult::Aborted;

}