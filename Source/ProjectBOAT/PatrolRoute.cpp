// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"
#include "Components/SplineComponent.h"


// Sets default values
APatrolRoute::APatrolRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	splineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	RootComponent = splineComponent;

}

// Called when the game starts or when spawned
void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Number of spline points in spline component %d"),splineComponent->GetNumberOfSplinePoints());
	for(int i = 1;i < numberOfPoints;i++){

		FVector pointPos = FVector(FMath::RandRange(-patrolPointRange,patrolPointRange),FMath::RandRange(-patrolPointRange,patrolPointRange),0);
		FSplinePoint splinePoint;
		splinePoint.Position = pointPos;
		splinePoint.Rotation = FRotator(0.0f,0.0f,0.0f);
		splinePoint.Scale = FVector(0.0f,0.0f,0.0f);
		splineComponent->AddPoint(splinePoint,true);

	}
	
}

// Called every frame
void APatrolRoute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

