// Fill out your copyright notice in the Description page of Project Settings.


#include "PirateShip.h"
#include "PlayerShip.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

APirateShip::APirateShip(){


}

void APirateShip::BeginPlay(){

    Super::BeginPlay();

    playerShip = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(this,0));

    if(weaponActor){

        GetWorldTimerManager().SetTimer(FireRateTimerHandle,this, &APirateShip::CheckFireCondition,weaponActor->FireRate,true);

    }

}

void APirateShip::Tick(float DeltaTime){

    Super::Tick(DeltaTime);


    //UE_LOG(LogTemp, Display, TEXT("Target Position %s"),*targetPosition.ToString());


    SetTarget();
    TurnWeapon(targetPosition);

    float distance = FVector::Dist(GetActorLocation(),targetPosition);

    if(isMovingToTarget && distance > shootRange && distance < aggroRange){

        MoveToTarget();

    }


}

void APirateShip::MoveToTarget(){

    //UE_LOG(LogTemp, Display, TEXT("Moving"));

    // SetActorRotation(FMath::RInterpTo(GetActorRotation(),
    //                     targetRotation,
    //                     UGameplayStatics::GetWorldDeltaSeconds(this),
    //                     turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)));

    // FVector moveDir = FVector::ZeroVector;
    // moveDir.X = moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	// AddActorLocalOffset(moveDir,true);

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

    if(playerShip){

        float distance = FVector::Dist(GetActorLocation(),playerShip->GetActorLocation());

        return (distance <= shootRange);
    }

    return false;
}


void APirateShip::Fire(){

    Super::Fire();



}