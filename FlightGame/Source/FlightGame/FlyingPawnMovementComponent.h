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

	bool WasDrifting;
	float DriftRoll;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float PitchVelocityDecay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float YawVelocityDecay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxYawVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxPitchVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float YawInputScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float PitchInputScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float PitchDecay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MinPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxForwardVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxStrafeVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float CruiseVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ForwardDragHigh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ForwardDragLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float StrafeVelocityDecay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	float ForwardVelocityDecay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	float RollFactor;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|PawnMovement")
	void AddPawnYawInput(float yaw);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|PawnMovement")
	void AddPawnPitchInput(float pitch);

	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	FVector InputVelocity;

	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	FVector DriftVelocity;

	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	FVector TotalVelocity;

	void Initialize();

};
