// Fill out your copyright notice in the Description page of Project Settings.


#include "PirateShip.h"
#include "PlayerShip.h"
#include "Dropbox.h"
#include "PirateAIController.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"

APirateShip::APirateShip(){

    // Setup the perception component
    // PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
    // sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    // PerceptionComponent->ConfigureSense(*sightConfig);
    // PerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());
    // PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &APirateShip::OnSightSensed);

}

void APirateShip::BeginPlay(){

    Super::BeginPlay();

    playerShip = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(this,0));
    controller =  Cast<APirateAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
    //sightConfig->SightRadius = controller->aggroRange;

    if(weaponActor){


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

    if(playerShip && controller){

        float distance = FVector::Dist(GetActorLocation(),playerShip->GetActorLocation());

        return (distance <= controller->shootRange);
    }

    return false;
}


void APirateShip::Fire(){

    Super::Fire();



}

// void APirateShip::OnSightSensed(const TArray<AActor*>&DetectedPawn){

//     UE_LOG(LogTemp, Display, TEXT("SOMETHING IS IN MY VISION"));

// }

void APirateShip::Die(){

    //Spawn dropbox of items

    if(dropbox != nullptr){

        auto dropBoxActor = GetWorld()->SpawnActor<ADropbox>(dropbox,GetActorLocation(),GetActorRotation());
        dropBoxActor->SetOwner(this);

        for(int i = 0; i < inventoryComponent->items.Num();i++){

		    dropBoxActor->items.Add(inventoryComponent->items[i]);

        }

	}

    TArray<AActor*> actors;

    GetAttachedActors(actors,false,true);

    for(int i = 0; i < actors.Num();i++){

        actors[i]->Destroy();

    }


    Destroy();

}