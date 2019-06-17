// Fill out your copyright notice in the Description page of Project Settings.


#include "InstantHitWeapon.h"
#include "FlyingPlayerController.h"
#include "VisualLogger.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Called every frame
void AInstantHitWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInstantHitWeapon::DoFireWeapon()
{
	const FVector AimDir = GetAdjustedAim();
	const FVector StartTrace = GetCameraDamageStartLocation(AimDir);
	const FVector ShootDir = AimDir;
	const FVector EndTrace = StartTrace + ShootDir * InstantConfig.WeaponRange;

	// Trace from the camera to the crosshairs.
	const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);

	// If we hit something, we'll perform another trace from the weapon muzzle.
	if (Impact.GetActor()) {
		FVector muzzleLocation = GetActorLocation();
		FRotator actorRotation = GetActorRotation();
		muzzleLocation += actorRotation.RotateVector(WeaponConfig.MuzzleOffset);
		FVector diff = Impact.ImpactPoint - muzzleLocation;
		diff.Normalize();
		const FHitResult ActualImpact = WeaponTrace(muzzleLocation, Impact.ImpactPoint + diff * 10);
		ProcessInstantHit(ActualImpact, muzzleLocation, ShootDir);
	}

}


// Called when the game starts or when spawned
void AInstantHitWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AInstantHitWeapon::ProcessInstantHit(FHitResult Impact, FVector StartTrace, FVector EndTrace)
{
	if (Impact.GetActor()) {
		FPointDamageEvent PointDmg;
		PointDmg.DamageTypeClass = InstantConfig.DamageType;
		PointDmg.HitInfo = Impact;
		PointDmg.ShotDirection = EndTrace - StartTrace;
		PointDmg.Damage = InstantConfig.HitDamage;
		AFlyingPlayerController* PC = MyPawn ? Cast<AFlyingPlayerController>(MyPawn->Controller) : NULL;
		Impact.GetActor()->TakeDamage(InstantConfig.HitDamage, PointDmg, PC, this);
		NotifyImpact(Impact);
	}

}

void AInstantHitWeapon::NotifyImpact_Implementation(FHitResult Impact) {

}
