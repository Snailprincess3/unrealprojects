// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VisualLogger.h"
#include "BaseWeapon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWeapon, Log, All);

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/** time between two consecutive shots */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float TimeBetweenShots;

	/** time between two consecutive shots */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	FVector MuzzleOffset;

	/** defaults */
	FWeaponData()
	{
		TimeBetweenShots = 0.2f;
		MuzzleOffset = FVector(10, 0, 0);
	}
};

UCLASS()
class FLIGHTGAME_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	/** [local + server] start weapon fire */
	virtual void StartFire();

	/** [local + server] stop weapon fire */
	virtual void StopFire();

	/** check if weapon can fire */
	bool CanFire() const;

	/** set the weapon's owning pawn */
	void SetOwningPawn(APawn* owningPawn);

	// Sets default values for this actor's properties
	ABaseWeapon();

private:

	bool ShouldFireNextFrame;

	bool WantsToFire;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** weapon data */
	UPROPERTY(EditAnywhere, Category = Config)
	FWeaponData WeaponConfig;

	class APawn* MyPawn;

	float LastFireTime;

	FVector GetAdjustedAim() const;

	FVector GetCameraDamageStartLocation(const FVector& AimDir) const;

	/** find hit */
	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo) const;

	virtual void DoFireWeapon();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
