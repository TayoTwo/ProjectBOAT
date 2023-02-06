// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMoveToTarget.h"
#include "AIController.h"

UBTTMoveToTarget::UBTTMoveToTarget(const FObjectInitializer &ObjectInitializer){



}

EBTNodeResult::Type UBTTMoveToTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory){

    //get AI controller and its NPC

    // auto const controller = Cast<AAIController>(OwnerComp.GetAIOwner());
    // ship = Cast<ABaseShip>(controller->GetPawn());

    // FVector targetPosition = get_blackboard()->GetValueAsVector("MoveTo");
    // FVector targetDir = targetPosition - ship->GetActorLocation();
    // targetDir.Z = 0;
    // FRotator targetRotation = targetDir.ToOrientationRotator();

    // ship->SetActorRotation(FMath::RInterpTo(pirateShip->GetActorRotation(),
    //                     targetRotation,
    //                     UGameplayStatics::GetWorldDeltaSeconds(this),
    //                     turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)));

    // FVector moveDir = FVector::ZeroVector;
    // moveDir.X = ship.moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	// AddActorLocalOffset(moveDir,true);

    UE_LOG(LogTemp, Display, TEXT("%s is moving to a target"),*ship->GetName());

    return EBTNodeResult::Type();

}

void UBTTMoveToTarget::OnGameplayTaskActivated(UGameplayTask &Task){

    Super::OnGameplayTaskActivated(Task);
    //MoveToTarget();

}

void UBTTMoveToTarget::MoveToTarget(){

    // UE_LOG(LogTemp, Display, TEXT("Moving"));

    // SetActorRotation(FMath::RInterpTo(GetActorRotation(),
    //                     targetRotation,
    //                     UGameplayStatics::GetWorldDeltaSeconds(this),
    //                     turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)));

    // FVector moveDir = FVector::ZeroVector;
    // moveDir.X = moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	// AddActorLocalOffset(moveDir,true);

}