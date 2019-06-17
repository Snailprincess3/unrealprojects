// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Engine/World.h"
#include "GameFramework/DamageType.h"
#include "InstantHitWeapon.generated.h"

USTRUCT()
struct FInstantWeaponData
{
	GENERATED_USTRUCT_BODY()

	/** base weapon spread (degrees) */
	UPROPERTY(EditDefaultsOnly, Category = Accuracy)
	float WeaponSpread;

	/** targeting spread modifier */
	UPROPERTY(EditDefaultsOnly, Category = Accuracy)
	float TargetingSpreadMod;

	/** continuous firing: spread increment */
	UPROPERTY(EditDefaultsOnly, Category = Accuracy)
	float FiringSpreadIncrement;

	/** continuous firing: max increment */
	UPROPERTY(EditDefaultsOnly, Category = Accuracy)
	float FiringSpreadMax;

	/** weapon range */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float WeaponRange;

	/** damage amount */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	int32 HitDamage;

	/** hit verification: scale for bounding box of hit actor */
	UPROPERTY(EditDefaultsOnly, Category = HitVerification)
	float ClientSideHitLeeway;

	/** hit verification: threshold for dot product between view direction and hit direction */
	UPROPERTY(EditDefaultsOnly, Category = HitVerification)
	float AllowedViewDotHitDir;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* BeamEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	AActor* DebugLocatorTemplate;

	UPROPERTY(EditDefaultsOnly, Category = WeaponState)
	TSubclassOf<UDamageType> DamageType;

	/** defaults */
	FInstantWeaponData()
	{
		WeaponSpread = 5.0f;
		TargetingSpreadMod = 0.25f;
		FiringSpreadIncrement = 1.0f;
		FiringSpreadMax = 10.0f;
		WeaponRange = 10000.0f;
		HitDamage = 10;
		ClientSideHitLeeway = 200.0f;
		AllowedViewDotHitDir = 0.8f;
		DamageType = UDamageType::StaticClass();
	}
};
/**
 * 
 */
UCLASS()
class FLIGHTGAME_API AInstantHitWeapon : public ABaseWeapon
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void DoFireWeapon() override;
	
	virtual void ProcessInstantHit(FHitResult Impact, FVector StartTrace, FVector EndTrace);

	/** weapon config */
	UPROPERTY(EditDefaultsOnly, Category = Config)
	FInstantWeaponData InstantConfig;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "WeaponEffect")
	void NotifyImpact(FHitResult Impact);


};
