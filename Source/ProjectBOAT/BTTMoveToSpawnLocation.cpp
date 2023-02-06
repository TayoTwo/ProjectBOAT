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



    return EBTNodeResult::Type();

}

void UBTTMoveToSpawnLocation::TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds){

    Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);

    if(ship != nullptr){

        auto const controller = Cast<APirateAIController>(OwnerComp.GetAIOwner());

        UBlackboardComponent* blackBoard = controller->GetBlackboardComponent(); 

        FVector spawnPosition = blackBoard->GetValueAsVector("SpawnLocation");
        FVector targetDir = spawnPosition - ship->GetActorLocation();
        targetDir.Z = 0;
        FRotator targetRotation = targetDir.ToOrientationRotator();

        // ship->SetActorRotation(FMath::RInterpTo(
        //                     ship->GetActorRotation(),
        //                     targetRotation,
        //                     UGameplayStatics::GetWorldDeltaSeconds(this),
        //                     ship->turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)
        //                      ));

        ship->SetActorRotation(targetRotation);

        FVector moveDir = FVector::ZeroVector;
        moveDir.X = ship->moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

        ship->AddActorLocalOffset(moveDir,true);

        UE_LOG(LogTemp, Display, TEXT("%s is moving to a target"),*ship->GetName());

    }

}

void UBTTMoveToSpawnLocation::OnGameplayTaskActivated(UGameplayTask &Task){

    Super::OnGameplayTaskActivated(Task);
    //MoveToTarget();

}