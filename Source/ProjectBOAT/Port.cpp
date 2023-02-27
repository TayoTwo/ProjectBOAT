// Fill out your copyright notice in the Description page of Project Settings.


#include "Port.h"
#include "Components/BoxComponent.h"

// Sets default values
APort::APort()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory Component");
	RootComponent = mesh;
	triggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	triggerVolume->SetupAttachment(mesh);

}

// Called when the game starts or when spawned
void APort::BeginPlay()
{
	Super::BeginPlay();
	triggerVolume->OnComponentBeginOverlap.AddDynamic(this,&APort::OnOverlapBegin);
	
}

// Called every frame
void APort::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APort::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){

	UE_LOG(LogTemp, Display, TEXT("VOLUME TRIGGERED"));



}