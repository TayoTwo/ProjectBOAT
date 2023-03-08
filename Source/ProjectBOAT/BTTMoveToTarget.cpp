// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMoveToTarget.h"
#include "PirateAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTMoveToTarget::UBTTMoveToTarget(const FObjectInitializer &ObjectInitializer){



}

EBTNodeResult::Type UBTTMoveToTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory){

    Super::ExecuteTask(OwnerComp,NodeMemory);
    //get AI controller and its NPC

    //UE_LOG(LogTemp, Display, TEXT("TASK EXECUTING"));
    bNotifyTick = true;
    controller = Cast<APirateAIController>(OwnerComp.GetAIOwner());
    ship = controller->ship;
    //AcceptableRadius = controller->shootRange;

    return EBTNodeResult::Type::InProgress;

}

void UBTTMoveToTarget::TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds){

    Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);

    //UE_LOG(LogTemp, Display, TEXT("TASK TICKING"));

    if(ship != nullptr){

        //UE_LOG(LogTemp, Display, TEXT("TASK MOVING"));

        UBlackboardComponent* blackBoard = controller->GetBlackboardComponent(); 

        FVector targetPosition = blackBoard->GetValueAsVector("MoveTo");

        float distance = FVector::Distance(ship->GetActorLocation(),targetPosition);

        FVector targetDir = targetPosition - ship->GetActorLocation();
        targetDir.Z = 0;
        FRotator targetRotation = targetDir.ToOrientationRotator();

        ship->SetActorRotation(FMath::RInterpTo(
                            ship->GetActorRotation(),
                            targetRotation,
                            UGameplayStatics::GetWorldDeltaSeconds(this),
                            ship->turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)
                             ));


        FVector moveDir = FVector::ZeroVector;
        moveDir.X = ship->moveSpeed * 0.02f;

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
