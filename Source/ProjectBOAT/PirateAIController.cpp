// Fill out your copyright notice in the Description page of Project Settings.


#include "PirateAIController.h"
#include "PatrolRoute.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


APirateAIController::APirateAIController(){

    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
    sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    PerceptionComponent->ConfigureSense(*sightConfig);
    PerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());
    PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &APirateAIController::OnSightSensed);
}

void APirateAIController::BeginPlay()
{
    Super::BeginPlay();

    ship = Cast<ABaseShip>(GetPawn());

    AttachToActor(ship,FAttachmentTransformRules::SnapToTargetIncludingScale,"");
    sightConfig->SightRadius = aggroRange;
    sightConfig->PeripheralVisionAngleDegrees = 90.f;

    if(ship != nullptr){

        UE_LOG(LogTemp, Display, TEXT("Ship actor "),*ship->GetName());
        patrolRouteActor = GetWorld()->SpawnActor<APatrolRoute>(patrolRoute,ship->GetActorLocation(),ship->GetActorRotation());
        SetupController();

    } else {

        UE_LOG(LogTemp, Display, TEXT("BEGIN PLAY SHIP IS NULL"));

    }

}

void APirateAIController::Tick(float DeltaSeconds){

    Super::Tick(DeltaSeconds);

    if(ship == nullptr){

        //UE_LOG(LogTemp, Display, TEXT("TICK SHIP IS NULL"));
        ship = Cast<ABaseShip>(GetPawn());
        patrolRouteActor = GetWorld()->SpawnActor<APatrolRoute>(patrolRoute,ship->GetActorLocation(),ship->GetActorRotation());
        AttachToActor(ship,FAttachmentTransformRules::SnapToTargetIncludingScale,"");

        SetupController();

    } 

    if(ship != nullptr && TargetPawn != nullptr){

        float disToTarget = FVector::Distance(TargetPawn->GetActorLocation(),ship->GetActorLocation());
        GetBlackboardComponent()->SetValueAsFloat("DistanceToPlayer",disToTarget);

        if(disToTarget < aggroRange && disToTarget > shootRange){

            //UE_LOG(LogTemp, Display, TEXT("CHASING"));
            GetBlackboardComponent()->SetValueAsVector("MoveTo",TargetPawn->GetActorLocation());
            GetBlackboardComponent()->SetValueAsEnum("State",static_cast<int>(EPirateState::Chasing));

        } else if(disToTarget <= shootRange){

            //UE_LOG(LogTemp, Display, TEXT("ATTACKING"));
            GetBlackboardComponent()->SetValueAsVector("ShootTarget",TargetPawn->GetActorLocation());
            GetBlackboardComponent()->SetValueAsEnum("State",static_cast<int>(EPirateState::Attacking));

        } else {

            //UE_LOG(LogTemp, Display, TEXT("PASSIVE"));
            GetBlackboardComponent()->SetValueAsEnum("State",static_cast<int>(EPirateState::Patroling));

        }

    }


}

void APirateAIController::SetupController(){

    TargetPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    UE_LOG(LogTemp, Display, TEXT("SETTING UP CONTROLLER"));

    if(AIBehaviorTree != nullptr){


        RunBehaviorTree(AIBehaviorTree);
        GetBlackboardComponent()->SetValueAsVector("MoveTo",patrolRouteActor->splineComponent->GetLocationAtSplinePoint(0,ESplineCoordinateSpace::Type::World));
        //GetBlackboardComponent()->SetValueAsFloat("FireRate",ship->weaponActor->FireRate);
        UE_LOG(LogTemp, Display, TEXT("CONTROLLER SET UP"));

    }

}

void APirateAIController::OnSightSensed(const TArray<AActor*>&DetectedPawn){

    UE_LOG(LogTemp, Display, TEXT("SOMETHING IS IN MY VISION"));

}