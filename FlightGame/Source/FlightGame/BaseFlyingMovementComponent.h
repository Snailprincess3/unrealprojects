// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"

#include "BaseFlyingMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FLIGHTGAME_API UBaseFlyingMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()


public:
	
	virtual void SetUseAccelerationForPathing(bool useAcceleration);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	virtual void RequestPathMove(const FVector& MoveInput) override;

	virtual void Initialize();

	void StopMovementKeepPathing();

private:

	float GetMinimumAngleDelta(float angle1, float angle2);

	float MaxSpeed;

};
