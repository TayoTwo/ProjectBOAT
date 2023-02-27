// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.h"
#include "Port.generated.h"

UCLASS()
class PROJECTBOAT_API APort : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APort();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UInventoryComponent* inventoryComponent;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* triggerVolume;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
