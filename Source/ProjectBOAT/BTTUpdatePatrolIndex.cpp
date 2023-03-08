// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTUpdatePatrolIndex.h"
#include "PatrolRoute.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTUpdatePatrolIndex::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory){

    Super::ExecuteTask(OwnerComp,NodeMemory);
    //get AI controller and its NPC

    //UE_LOG(LogTemp, Display, TEXT("TASK EXECUTING"));
    //bNotifyTick = true;
    controller = Cast<APirateAIController>(OwnerComp.GetAIOwner());

    UBlackboardComponent* blackBoard = controller->GetBlackboardComponent(); 

    if(blackBoard){

        //FVector targetPosition = blackBoard->GetValueAsVector("MoveTo");
        int patrolIndex = blackBoard->GetValueAsInt("PatrolIndex");
        APatrolRoute* patrolRoute = controller->patrolRouteActor;

        //UE_LOG(LogTemp, Display, TEXT("NUMBER OF SPLINE POINTS %d"),patrolRoute->splineComponent->GetNumberOfSplinePoints());
        if(patrolIndex >= patrolRoute->splineComponent->GetNumberOfSplinePoints()){

            patrolIndex = 0;

        } else {

            patrolIndex++;

        }

        blackBoard->SetValueAsInt("PatrolIndex",patrolIndex);

        blackBoard->SetValueAsVector("MoveTo",patrolRoute->splineComponent->GetLocationAtSplinePoint(patrolIndex,ESplineCoordinateSpace::Type::World));

        return EBTNodeResult::Succeeded;

    }
    
    return EBTNodeResult::Failed;

}

void UBTTUpdatePatrolIndex::TickTask(UBehaviorTreeComponent &OwnerComp,uint8 * NodeMemory,float DeltaSeconds){

    Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);



}

void UBTTUpdatePatrolIndex::OnGameplayTaskActivated(UGameplayTask &Task){

    Super::OnGameplayTaskActivated(Task);
    //MoveToTarget();

}
