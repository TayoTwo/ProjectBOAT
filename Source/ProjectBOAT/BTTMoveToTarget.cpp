// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMoveToTarget.h"
#include "PirateAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTMoveToTarget::UBTTMoveToTarget(const FObjectInitializer &ObjectInitializer){

    bNotifyTick = true;
    bTickIntervals = true;

}

EBTNodeResult::Type UBTTMoveToTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory){

    Super::ExecuteTask(OwnerComp,NodeMemory);
    //get AI controller and its NPC

    //UE_LOG(LogTemp, Display, TEXT("TASK EXECUTING"));

    controller = Cast<APirateAIController>(OwnerComp.GetAIOwner());
    ship = controller->ship;
    //AcceptableRadius = controller->shootRange;
    SetNextTickTime(NodeMemory, TickInterval);

    return EBTNodeResult::Type::InProgress;

}

void UBTTMoveToTarget::TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds){

    Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);

    //UE_LOG(LogTemp, Display, TEXT("TASK TICKING"));

    if(ship != nullptr){

        //UE_LOG(LogTemp, Display, TEXT("Delta Seconds %f"),DeltaSeconds);

        UBlackboardComponent* blackBoard = controller->GetBlackboardComponent(); 

        FVector targetPosition = blackBoard->GetValueAsVector("MoveTo");

        float distance = FVector::Distance(ship->GetActorLocation(),targetPosition);

        FVector targetDir = targetPosition - ship->GetActorLocation();
        targetDir.Z = 0;
        FRotator targetRotation = targetDir.ToOrientationRotator();

        ship->SetActorRotation(FMath::RInterpTo(
                            ship->GetActorRotation(),
                            targetRotation,
                            TickInterval,
                            ship->turnSpeed * TickInterval
                             ));


        moveDir = FVector::ZeroVector;
        moveDir.X = ship->moveSpeed * TickInterval;

        //UE_LOG(LogTemp, Display, TEXT("%s MOVE SPEED %f"),*ship->GetName(),moveDir.X);

        ship->AddActorLocalOffset(moveDir,true);

        if(distance < AcceptableRadius){

            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            //UE_LOG(LogTemp, Display, TEXT("TASK IS FINISHED"));

        } else {

            //UE_LOG(LogTemp, Display, TEXT("TASK IS IN PROGRESS"));

        }

        //UE_LOG(LogTemp, Display, TEXT("Distance to target %f / %f"),distance,AcceptableRadius);

    }

}

void UBTTMoveToTarget::OnGameplayTaskActivated(UGameplayTask &Task){

    Super::OnGameplayTaskActivated(Task);
    //MoveToTarget();

}
