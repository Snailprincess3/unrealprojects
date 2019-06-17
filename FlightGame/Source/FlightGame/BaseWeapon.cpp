// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "FlyingPlayerController.h"
#include "FlyingPawn.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(LogWeapon);

void ABaseWeapon::StartFire()
{
	WantsToFire = true;
}

void ABaseWeapon::StopFire()
{
	WantsToFire = false;
}

bool ABaseWeapon::CanFire() const
{
	return (GetWorld()->GetTimeSeconds() - LastFireTime) > WeaponConfig.TimeBetweenShots;
}

void ABaseWeapon::SetOwningPawn(APawn * owningPawn)
{
	MyPawn = owningPawn;
}

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WantsToFire && CanFire()) {
		DoFireWeapon();
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void ABaseWeapon::DoFireWeapon() {

}

FVector ABaseWeapon::GetAdjustedAim() const
{
	AFlyingPlayerController* const PlayerController = Instigator ? Cast<AFlyingPlayerController>(Instigator->Controller) : NULL;
	AFlyingPawn* const FlyingPawn = MyPawn ? Cast<AFlyingPawn>(MyPawn) : NULL;
	FVector FinalAim = FVector::ZeroVector;
	// If we have a player controller use it for the aim
	if (PlayerController && FlyingPawn)
	{
		FVector CamLoc;
		FRotator UnusedRot;
		PlayerController->GetPlayerViewPoint(CamLoc, UnusedRot);
		FVector aimMarkerPos = FlyingPawn->AimMarker->GetComponentLocation();
		FinalAim = aimMarkerPos - CamLoc;
	}

	return FinalAim;
}

FVector ABaseWeapon::GetCameraDamageStartLocation(const FVector& AimDir) const
{
	AFlyingPlayerController* PC = MyPawn ? Cast<AFlyingPlayerController>(MyPawn->Controller) : NULL;
	FVector OutStartTrace = FVector::ZeroVector;

	if (PC)
	{
		// use player's camera
		FRotator UnusedRot;
		PC->GetPlayerViewPoint(OutStartTrace, UnusedRot);
	}


	return OutStartTrace;
}

FHitResult ABaseWeapon::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const
{

	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, Instigator);
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_WorldDynamic, TraceParams);

	return Hit;
}
 