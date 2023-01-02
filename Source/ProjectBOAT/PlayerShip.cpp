// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

APlayerShip::APlayerShip(){

    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    springArm->SetupAttachment(RootComponent);

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera->SetupAttachment(springArm);

}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Vertical"),this,&APlayerShip::MoveVertical);

    PlayerInputComponent->BindAxis(TEXT("Horizontal"),this,&APlayerShip::MoveHorizontal);

    PlayerInputComponent->BindAction(TEXT("LMB"),IE_Pressed,this,&APlayerShip::Fire);

    PlayerInputComponent->BindAction(TEXT("RMB"),IE_Pressed,this,&APlayerShip::SetTarget);

}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();

    PlayerController = Cast<APlayerController>(GetController());
	
}

void APlayerShip::Tick(float DeltaTime){

    Super::Tick(DeltaTime);

    if(PlayerController){

        FHitResult hitResult;
        PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false, hitResult);

        DrawDebugSphere(GetWorld(),
                        hitResult.ImpactPoint,
                        25.f,
                        12,
                        FColor::Green,
                        false,
                        -1.f);

        if(isMovingToTarget){

            MoveToTarget();

        }

    }

}

void APlayerShip::MoveVertical(float value){

    //(LogTemp, Warning, TEXT("Vertical Dir: %f"),value);

    FVector moveDir = FVector::ZeroVector;
    moveDir.X = value * moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalOffset(moveDir,true);

}

void APlayerShip::MoveHorizontal(float value){

    if(value != 0){

        isMovingToTarget = false;

    }

    //UE_LOG(LogTemp, Warning, TEXT("Horizontal Dir: %f"),value);

    FRotator turnDir = FRotator::ZeroRotator;

    turnDir.Yaw = value * turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalRotation(turnDir,true);

}

void APlayerShip::MoveToTarget(){

    float distanceToTarget = FVector::Distance(targetPosition,GetActorLocation());

    if(PlayerController && distanceToTarget > toTargetDistance){

        UE_LOG(LogTemp, Display, TEXT("Moving to target"));

        FVector targetDir = targetPosition - GetActorLocation();
        targetDir.Z = 0;
        FRotator targetRotation = targetDir.ToOrientationRotator();

        SetActorRotation(FQuat::Slerp(GetActorRotation(),targetRotation,turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)));
        MoveVertical(1.f);

    } else {

        UE_LOG(LogTemp, Display, TEXT("Target at position"));
        isMovingToTarget = false;

    }

}

void APlayerShip::SetTarget(){

    if(PlayerController){

        FHitResult hitResult;
        PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false, hitResult);

        DrawDebugSphere(GetWorld(),
                        hitResult.ImpactPoint,
                        25.f,
                        12,
                        FColor::Red,
                        false,
                        3.f);

        targetPosition = hitResult.ImpactPoint;
        isMovingToTarget = true;

    }

}