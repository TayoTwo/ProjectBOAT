// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTShootTarget.h"
#include "PirateAIController.h"
#include "Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTShootTarget::UBTTShootTarget(const FObjectInitializer &ObjectInitializer){


}

EBTNodeResult::Type UBTTShootTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory){

    UE_LOG(LogTemp, Display, TEXT("TASK EXECUTING"));
    bNotifyTick = true;
    controller = Cast<APirateAIController>(OwnerComp.GetAIOwner());
    ship = controller->ship;
    weaponActor = controller->ship->weaponActor;

    if(weaponActor){

        ship->GetWorldTimerManager().SetTimer(ship->FireRateTimerHandle,ship, &ABaseShip::Fire,weaponActor->FireRate,true);

    }

    return EBTNodeResult::Type::InProgress;

}

void UBTTShootTarget::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds){

    if(ship != nullptr){

        UBlackboardComponent* blackBoard = controller->GetBlackboardComponent(); 
        FVector targetPosition = blackBoard->GetValueAsVector("ShootTarget");
        float distance = FVector::Distance(ship->GetActorLocation(),targetPosition);

        ship->TurnWeapon(targetPosition);

    }

}

void UBTTShootTarget::OnGameplayTaskActivated(UGameplayTask &Task){



}