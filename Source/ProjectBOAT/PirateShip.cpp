// Fill out your copyright notice in the Description page of Project Settings.


#include "PirateShip.h"
#include "PlayerShip.h"
#include "PirateAIController.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"

APirateShip::APirateShip(){

    // Setup the perception component
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
    sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    PerceptionComponent->ConfigureSense(*sightConfig);
    PerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());
    PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &APirateShip::OnSightSensed);

}

void APirateShip::BeginPlay(){

    Super::BeginPlay();

    playerShip = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(this,0));
    controller =  Cast<APirateAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
    sightConfig->SightRadius = controller->aggroRange;

    if(weaponActor){

        GetWorldTimerManager().SetTimer(FireRateTimerHandle,this, &APirateShip::CheckFireCondition,weaponActor->FireRate,true);

    }

}

void APirateShip::Tick(float DeltaTime){

    Super::Tick(DeltaTime);


    //UE_LOG(LogTemp, Display, TEXT("Target Position %s"),*targetPosition.ToString());


    //SetTarget();
    //TurnWeapon(targetPosition);

}


void APirateShip::SetTarget(){

    if(playerShip){

        targetPosition = playerShip->GetActorLocation();

        isMovingToTarget = true;

        FVector targetDir = targetPosition - GetActorLocation();
        targetDir.Z = 0;
        targetRotation = targetDir.ToOrientationRotator();

    }

}

void APirateShip::CheckFireCondition(){

    if(CanFire()){

        //UE_LOG(LogTemp, Display, TEXT("FIRE"));
        Fire();

    }

}

bool APirateShip::CanFire(){

    // if(playerShip){

    //     float distance = FVector::Dist(GetActorLocation(),playerShip->GetActorLocation());

    //     return (distance <= shootRange);
    // }

    return false;
}


void APirateShip::Fire(){

    Super::Fire();



}

void APirateShip::OnSightSensed(const TArray<AActor*>&DetectedPawn){

    UE_LOG(LogTemp, Display, TEXT("SOMETHING IS IN MY VISION"));

}