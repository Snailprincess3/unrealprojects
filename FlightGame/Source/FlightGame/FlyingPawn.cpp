// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingPawn.h"
#include "FlyingPawnMovementComponent.h"
#include "BaseWeapon.h"
#include "Components/InputComponent.h"


// Sets default values
AFlyingPawn::AFlyingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	AimMarker = CreateDefaultSubobject<USceneComponent>(TEXT("AimComponent"));
	//RootComponent = PawnMesh;
	FlightMovementComponent = CreateDefaultSubobject<UFlyingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	FlightMovementComponent->UpdatedComponent = RootComponent;
	FlightMovementComponent->bEditableWhenInherited = true;
	FlightMovementComponent->Initialize();
	PawnMesh->SetupAttachment(RootComponent);
	AimMarker->SetupAttachment(PawnMesh);

	PawnMesh->bEditableWhenInherited = true;
	AimMarker->bEditableWhenInherited = true;

}

// Called when the game starts or when spawned
void AFlyingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlyingPawn::MoveForward(float val)
{
	FlightMovementComponent->AddInputVector(FVector(0.0, val * FMath::Abs(val), 0.0));
}

void AFlyingPawn::MoveRight(float val)
{
	FlightMovementComponent->AddInputVector(FVector(val * FMath::Abs(val),0.0, 0.0));
}

void AFlyingPawn::TiltRight(float val)
{
	FlightMovementComponent->AddPawnYawInput(val * FMath::Abs(val));
}

void AFlyingPawn::TiltDown(float val)
{
	FlightMovementComponent->AddPawnPitchInput(-val * FMath::Abs(val));
}

void AFlyingPawn::StartPrimaryFire()
{
	printf("starting primary fire");
	if (CurrentWeapon == NULL) {
		return;
	}

	CurrentWeapon->StartFire();
}

void AFlyingPawn::EndPrimaryFire()
{
	if (CurrentWeapon == NULL) {
		return;
	}

	CurrentWeapon->StopFire();
}

// Called every frame
void AFlyingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlyingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFlyingPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFlyingPawn::MoveRight);
	PlayerInputComponent->BindAxis("TiltRight", this, &AFlyingPawn::TiltRight);
	PlayerInputComponent->BindAxis("TiltDown", this, &AFlyingPawn::TiltDown);

	PlayerInputComponent->BindAction("RightTrigger", IE_Pressed, this, &AFlyingPawn::StartPrimaryFire);
	PlayerInputComponent->BindAction("RightTrigger", IE_Released, this, &AFlyingPawn::EndPrimaryFire);
}

void AFlyingPawn::SetCurrentWeapon(ABaseWeapon * newWeapon)
{
	CurrentWeapon = newWeapon;
	if (newWeapon != NULL) {
		newWeapon->SetOwningPawn(this);

	}
}

ABaseWeapon * AFlyingPawn::GetCurrentWeapon()
{
	return CurrentWeapon;
}


