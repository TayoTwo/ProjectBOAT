// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Weapon.h"
#include "Target.h"

//#include "Blueprint/UserWidget.h" Apparently this is an intellisense issue
//#include "Runtime/UMG/Public/Blueprint/UserWidget.h";

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
    PlayerInputComponent->BindAction(TEXT("Space"),IE_Pressed,this,&APlayerShip::StopMovement);

    PlayerInputComponent->BindAction(TEXT("Tab"),IE_Pressed,this,&APlayerShip::ShowInventory);

}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();

    if(PlayerController == nullptr){

        PlayerController = Cast<APlayerController>(GetController());

    }

    PlayerController->bShowMouseCursor = true; 
    PlayerController->bEnableClickEvents = true; 
    PlayerController->bEnableMouseOverEvents = true;

    spawnPos = GetActorLocation();
 
    GetWorldTimerManager().SetTimer(timerHandle,this, &APlayerShip::ChangeFireState,weaponActor->FireRate,true);
	
}

void APlayerShip::Tick(float DeltaTime){

    Super::Tick(DeltaTime);

    if(PlayerController){

        //UE_LOG(LogTemp, Display, TEXT("PLAYER CONTROLLER FOUND"));
        FHitResult hitResult;
        PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false, hitResult);

        DrawDebugSphere(GetWorld(),
                        hitResult.ImpactPoint,
                        100.f,
                        12,
                        FColor::Green,
                        false,
                        -1.f);

        TurnWeapon(hitResult.ImpactPoint);

        if(isMovingToTarget){

            MoveToTarget();

        }

    }

}

//Check to see if the inventory widget is set than add it to our viewport
void APlayerShip::ShowInventory(){

    UE_LOG(LogTemp, Warning, TEXT("Show inventory pressed"));

    // if(inventoryWidget){

    //     // UUserWidget* widget = CreateWidget<UUserWidget>(PlayerController,inventoryWidget,TEXT("Inventory"));
    //     // widget->AddToViewport();

    // }

}

void APlayerShip::StopMovement(){

    isMovingToTarget = false;

}

void APlayerShip::MoveVertical(float value){

    //(LogTemp, Warning, TEXT("Vertical Dir: %f"),value);

    FVector moveDir = FVector::ZeroVector;
    moveDir.X = value * moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

    //UE_LOG(LogTemp, Warning, TEXT("MOVE DIR %f"),moveDir.X);

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

    //UE_LOG(LogTemp, Display, TEXT("Moving"));

    float distance = FVector::Distance(targetPosition,GetActorLocation());

    //UE_LOG(LogTemp, Display, TEXT("DISTANCE TO TARGET: %f"),distance);
    
    FVector targetDir = targetPosition - GetActorLocation();
    targetDir.Z = 0;
    targetRotation = targetDir.ToOrientationRotator();

    if(distance > keepDriftingDistance && !bIsDrifting){

        SetActorRotation(FMath::RInterpTo(
                        GetActorRotation(),
                        targetRotation,
                        UGameplayStatics::GetWorldDeltaSeconds(this),
                        turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)
                        ));

        // SetRelativeRotation(FMath::RInterpTo(
        //                 GetActorRotation(),
        //                 targetRotation,
        //                 UGameplayStatics::GetWorldDeltaSeconds(this),
        //                 turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)
        //                 ),
        //                 true
        //                 );

        //AddActorWorldRotation();
    } else {

        bIsDrifting = true;

    }

    MoveVertical(1.f);

}

void APlayerShip::SetTarget(){

    if(PlayerController){

        UE_LOG(LogTemp, Display, TEXT("SETTING TARGET"));

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
        bIsDrifting = false;

    }

}

void APlayerShip::Fire(){

    if(canFire){

        Super::Fire();
        UE_LOG(LogTemp, Display, TEXT("FIRE!"));
        canFire = false;

    }

    // if(PlayerController){

    //     FHitResult hitResult;
    //     PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false, hitResult);
	//     // EnemyTarget = Cast<AActor>(GetWorld()->SpawnActor<ATarget>(
    //     //     hitResult.ImpactPoint,
    //     //     GetActorRotation()
    //     //     ));

    // }

}

void APlayerShip::ChangeFireState(){

    canFire = true;

}

void APlayerShip::Die(){

    Super::Die();
    //Respawn

    FVector diePos = GetActorLocation();
    
    SetActorLocation(spawnPos);

    if(dropbox != nullptr){

        auto dropBoxActor = GetWorld()->SpawnActor<ADropbox>(dropbox,diePos,GetActorRotation());
        dropBoxActor->SetOwner(this);

        for(int i = 0; i < inventoryComponent->inventoryItems.Num();i++){

		    dropBoxActor->items.Add(inventoryComponent->inventoryItems[i]);

        }

	}

    //inventoryComponent->inventoryItems.Empty();
    healthComponent->Health = healthComponent->MaxHealth;

    UE_LOG(LogTemp, Display,TEXT("PLAYER DIED"));

    // TArray<AActor*> actors;

    // GetAttachedActors(actors,false,true);

    // for(int i = 0; i < actors.Num();i++){

    //     actors[i]->Destroy();

    // }

    //Destroy();

}

void APlayerShip::EquipItem(UItem* item){

    //UE_LOG(LogTemp, Display, TEXT("Equiping a %s"),item->itemName);

}