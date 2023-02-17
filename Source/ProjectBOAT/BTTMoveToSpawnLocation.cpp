// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMoveToSpawnLocation.h"
#include "PirateAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTMoveToSpawnLocation::UBTTMoveToSpawnLocation(const FObjectInitializer &ObjectInitializer){



}

EBTNodeResult::Type UBTTMoveToSpawnLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory){

    Super::ExecuteTask(OwnerComp,NodeMemory);
    //get AI controller and its NPC

    //UE_LOG(LogTemp, Display, TEXT("TASK EXECUTING"));
    bNotifyTick = true;
    controller = Cast<APirateAIController>(OwnerComp.GetAIOwner());
    ship = controller->ship;

    return EBTNodeResult::Type::InProgress;

}

void UBTTMoveToSpawnLocation::TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds){

    Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);

    //UE_LOG(LogTemp, Display, TEXT("TASK TICKING"));

    if(ship != nullptr){

        UBlackboardComponent* blackBoard = controller->GetBlackboardComponent(); 

        FVector spawnPosition = blackBoard->GetValueAsVector("SpawnLocation");
        float distance = FVector::Distance(ship->GetActorLocation(),spawnPosition);
        FVector targetDir = spawnPosition - ship->GetActorLocation();
        targetDir.Z = 0;
        FRotator targetRotation = targetDir.ToOrientationRotator();

        ship->SetActorRotation(FMath::RInterpTo(
                            ship->GetActorRotation(),
                            targetRotation,
                            UGameplayStatics::GetWorldDeltaSeconds(this),
                            ship->turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)
                             ));


        FVector moveDir = FVector::ZeroVector;
        moveDir.X = ship->moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

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

void UBTTMoveToSpawnLocation::OnGameplayTaskActivated(UGameplayTask &Task){

    Super::OnGameplayTaskActivated(Task);
    //MoveToTarget();

}