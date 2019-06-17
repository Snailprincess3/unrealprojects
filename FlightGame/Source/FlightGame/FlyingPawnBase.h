// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyingPawnBase.generated.h"

UCLASS()
class FLIGHTGAME_API AFlyingPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlyingPawnBase();

	float CurrentHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class UBaseFlyingMovementComponent* FlightMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UPROPERTY(EditDefaultsOnly, Category = Stats)
	float MaxHealth;
};
