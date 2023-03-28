// Fill out your copyright notice in the Description page of Project Settings.


#include "Dropbox.h"
#include "InventoryComponent.h"
#include "Components/BoxComponent.h" 

// Sets default values
ADropbox::ADropbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = boxComponent;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dropbox Mesh"));
	mesh->SetupAttachment(boxComponent);

}

// Called when the game starts or when spawned
void ADropbox::BeginPlay()
{
	Super::BeginPlay();
	boxComponent->OnComponentHit.AddDynamic(this,&ADropbox::OnHit);

}

// Called every frame
void ADropbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropbox::DropItems(UInventoryComponent* inventory){

	UE_LOG(LogTemp, Display, TEXT("DROPPING ITEMS"));

	for(int i = 0; i < items.Num();i++){

		inventory->AddItem(items[i]);

	}


}


void ADropbox::OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit){

	UE_LOG(LogTemp, Display, TEXT("HIT DROPBOX"));

	if(!bIsBossDropBox){

		auto MyOwner = GetOwner();

		if(MyOwner == nullptr || OtherActor == nullptr) return;

		auto MyOwnerInstigator = MyOwner->GetInstigatorController();
		auto DamageTypeClass = UDamageType::StaticClass();

		if(OtherActor != MyOwner && OtherActor->FindComponentByClass<UInventoryComponent>() != nullptr){

			UInventoryComponent* inventory = OtherActor->FindComponentByClass<UInventoryComponent>();

			DropItems(inventory);

			Destroy();

		}


	}


	//UE_LOG(LogTemp,Warning, TEXT("%s hit %s's %s"),*HitComp->GetName(),*OtherActor->GetName(),*OtherComp->GetName());

}
