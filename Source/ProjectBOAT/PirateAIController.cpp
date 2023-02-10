// Fill out your copyright notice in the Description page of Project Settings.


#include "PirateAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


APirateAIController::APirateAIController(){

    // Setup the perception component
    // PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
    // sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    // PerceptionComponent->ConfigureSense(*sightConfig);
    // PerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());
    // PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &APirateAIController::OnSightSensed);

}

void APirateAIController::BeginPlay()
{
    Super::BeginPlay();

    ship = Cast<ABaseShip>(GetPawn());
    AttachToActor(ship,FAttachmentTransformRules::SnapToTargetIncludingScale,"");

    if(ship != nullptr){

        UE_LOG(LogTemp, Display, TEXT("Ship actor "),*ship->GetName());
        SetupController();

    } else {

        UE_LOG(LogTemp, Display, TEXT("SHIP IS NULL"));

    }

}

void APirateAIController::Tick(float DeltaSeconds){

    Super::Tick(DeltaSeconds);

    if(ship == nullptr){

        UE_LOG(LogTemp, Display, TEXT("SHIP IS NULL"));
        ship = Cast<ABaseShip>(GetPawn());
        SetupController();


    } 

    if(ship != nullptr && TargetPawn != nullptr){

        float disToTarget = FVector::Distance(TargetPawn->GetActorLocation(),ship->GetActorLocation());

        //CHANGE THIS TO PERCEPTION COMPONENT 
        if(LineOfSightTo(TargetPawn) && disToTarget < aggroRange && disToTarget > shootRange){

            //UE_LOG(LogTemp, Display, TEXT("CHASING"));
            GetBlackboardComponent()->SetValueAsVector("MoveTo",TargetPawn->GetActorLocation());
            GetBlackboardComponent()->SetValueAsEnum("State",static_cast<int>(EPirateState::Chasing));

        } else if(LineOfSightTo(TargetPawn) && disToTarget <= shootRange){

            //UE_LOG(LogTemp, Display, TEXT("ATTACKING"));
            GetBlackboardComponent()->SetValueAsVector("ShootTarget",TargetPawn->GetActorLocation());
            GetBlackboardComponent()->SetValueAsEnum("State",static_cast<int>(EPirateState::Attacking));

        } else {

            //UE_LOG(LogTemp, Display, TEXT("PASSIVE"));
            GetBlackboardComponent()->SetValueAsEnum("State",static_cast<int>(EPirateState::Passive));

        }

    }


}

void APirateAIController::SetupController(){

    TargetPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(AIBehaviorTree != nullptr){

        RunBehaviorTree(AIBehaviorTree);
        GetBlackboardComponent()->SetValueAsVector(TEXT("SpawnLocation"),ship->GetActorLocation());
        //currentState = GetBlackboardComponent()->GetValueAsEnum("State");

    }

}

// void APirateAIController::OnSightSensed(){

//     UE_LOG(LogTemp, Display, TEXT("SOMETHING IS IN MY VISION"));

// }