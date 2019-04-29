// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingPawn.h"
#include "FlyingPawnMovementComponent.h"

// Sets default values
AFlyingPawn::AFlyingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlightMovementComponent = CreateDefaultSubobject<UFlyingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	FlightMovementComponent->UpdatedComponent = RootComponent;
	FlightMovementComponent->bEditableWhenInherited = true;
	FlightMovementComponent->Initialize();
}

// Called when the game starts or when spawned
void AFlyingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlyingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UPawnMovementComponent* AFlyingPawn::GetMovementComponent() const
{
	return FlightMovementComponent;
}

UFlyingPawnMovementComponent* AFlyingPawn::GetFlyingMovementComponent() const
{
	return FlightMovementComponent;
}

