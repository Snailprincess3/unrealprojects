// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingPawnBase.h"
#include "BaseFlyingMovementComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AFlyingPawnBase::AFlyingPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FlightMovementComponent = CreateDefaultSubobject<UBaseFlyingMovementComponent>(TEXT("CustomMovementComponent"));
	FlightMovementComponent->UpdatedComponent = RootComponent;
	FlightMovementComponent->bEditableWhenInherited = true;
	FlightMovementComponent->Initialize();
}

// Called when the game starts or when spawned
void AFlyingPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyingPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPawnMovementComponent* AFlyingPawnBase::GetMovementComponent() const
{
	return FlightMovementComponent;
}
