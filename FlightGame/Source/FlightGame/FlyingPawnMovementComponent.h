// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "FlyingPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FLIGHTGAME_API UFlyingPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	float YawInput;
	float YawVelocity;
	float PitchInput;
	float PitchVelocity;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|PawnMovement")
	void AddPawnYawInput(float yaw);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|PawnMovement")
	void AddPawnPitchInput(float pitch);

};
