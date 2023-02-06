// Fill out your copyright notice in the Description page of Project Settings.


#include "PirateAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void APirateAIController::BeginPlay()
{
    Super::BeginPlay();

    ship = Cast<ABaseShip>(GetOwner());

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

        ship = Cast<ABaseShip>(GetOwner());
        SetupController();

    }

}

void APirateAIController::SetupController(){

    if(AIBehaviorTree != nullptr){

        RunBehaviorTree(AIBehaviorTree);
        GetBlackboardComponent()->SetValueAsVector(TEXT("SpawnLocation"),ship->GetActorLocation());

    }

}