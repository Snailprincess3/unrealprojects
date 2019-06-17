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

	CurrentHealth = MaxHealth;
	
}

// Called every frame
void AFlyingPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFlyingPawnBase::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0) {
		CurrentHealth -= ActualDamage;

		if (CurrentHealth <= 0) {
			SetLifeSpan(0.001);
		}
	}

	return ActualDamage;
}

UPawnMovementComponent* AFlyingPawnBase::GetMovementComponent() const
{
	return FlightMovementComponent;
}
