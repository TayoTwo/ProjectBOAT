// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "Dropbox.generated.h"

UCLASS()
class PROJECTBOAT_API ADropbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropbox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DropItems(class UInventoryComponent* inventory);
	UPROPERTY(EditAnywhere)
	TArray<FItem> items;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;
	// UPROPERTY(EditAnywhere)
	// class UBoxComponent* boxComponent;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit);

};
