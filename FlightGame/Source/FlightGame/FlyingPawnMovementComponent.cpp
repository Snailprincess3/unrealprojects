// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingPawnMovementComponent.h"


void UFlyingPawnMovementComponent::AddPawnYawInput(float yaw) {
	YawInput += yaw;
};

void UFlyingPawnMovementComponent::AddPawnPitchInput(float pitch) {
	PitchInput += pitch;
}


void UFlyingPawnMovementComponent::Initialize() {
	InputVelocity.X = 0;
	InputVelocity.Y = 0;
	InputVelocity.Z = 0;

	WasDrifting = false;
	DriftRoll = 0;
	DriftVelocity.X = 0;
	DriftVelocity.Y = 0;
	DriftVelocity.Z = 0;
	TotalVelocity.X = 0;
	TotalVelocity.Y = 0;
	TotalVelocity.Z = 0;
}

void UFlyingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FVector currentInput = ConsumeInputVector().GetClampedToMaxSize(1.0f);
	bool drifting = currentInput.IsNearlyZero();
	if (drifting && !WasDrifting) {
		DriftRoll = YawVelocity / MaxYawVelocity * RollFactor;
	}
	if (drifting) {
		DriftVelocity = TotalVelocity;
	}
	WasDrifting = drifting;

	PitchVelocity += PitchInput * DeltaTime * PitchInputScale;
	PitchVelocity = FMath::Clamp(PitchVelocity, -MaxPitchVelocity, MaxPitchVelocity);
	
	YawVelocity += YawInput * DeltaTime * YawInputScale;
	YawVelocity = FMath::Clamp(YawVelocity, -MaxYawVelocity, MaxYawVelocity);

	float targetYaw = MaxYawVelocity * YawInput;
	float yawDelta = YawVelocity - targetYaw;
	YawVelocity = targetYaw + yawDelta * FMath::Pow(YawVelocityDecay, DeltaTime / 0.015);

	FRotator yaw;
	yaw.Pitch = 0;
	yaw.Yaw = YawVelocity * DeltaTime;
	yaw.Roll = 0;

	FRotator pitch;
	pitch.Pitch = PitchVelocity * DeltaTime;
	pitch.Yaw = 0;
	pitch.Roll = 0;

	FRotator roll;
	roll.Pitch = 0;
	roll.Yaw = 0;
	roll.Roll = YawVelocity / MaxYawVelocity * RollFactor ;

	if (drifting) {
		InputVelocity.X = 0;
		InputVelocity.Y = 0;
		InputVelocity.Z = 0;
		roll.Roll = DriftRoll;
	}
	else {
		InputVelocity += currentInput * DeltaTime * Acceleration;
		InputVelocity.X = FMath::Clamp(InputVelocity.X, 0.0f, MaxForwardVelocity);
		InputVelocity.Y = FMath::Clamp(InputVelocity.Y, -MaxStrafeVelocity, MaxStrafeVelocity);
		if (FMath::Abs(roll.Roll) < FMath::Abs(DriftRoll)) {
			roll.Roll = DriftRoll;
		}
		DriftVelocity *= FMath::Pow(DriftVelocityDecay, DeltaTime / 0.015);
	}


	DriftRoll *= FMath::Pow(0.95, DeltaTime / 0.015);

	FRotator currentRotation = UpdatedComponent->GetComponentRotation();
	float oldRoll = currentRotation.Roll;
	float delta = roll.Roll - oldRoll;
	delta = FMath::Clamp(delta, -MaxRollRate * DeltaTime, MaxRollRate * DeltaTime);
	roll.Roll = oldRoll + delta;
	currentRotation.Roll = 0;
	currentRotation += yaw;
	currentRotation += pitch;

	currentRotation.Pitch = FMath::Clamp(currentRotation.Pitch, MinPitch, MaxPitch);
	if (FMath::Abs(PitchInput) < 0.5) {
		PitchVelocity = PitchVelocity * FMath::Pow(PitchVelocityDecay, DeltaTime / 0.015);
		currentRotation.Pitch *= FMath::Pow(PitchDecay, DeltaTime / 0.015);
	}

	FVector targetVelocity = currentRotation.RotateVector(InputVelocity);

	currentRotation += roll;
	TotalVelocity = DriftVelocity + targetVelocity;
	float speed;
	TotalVelocity.ToDirectionAndLength(TotalVelocity, speed);

	if (speed > CruiseVelocity) {
		speed -= DeltaTime * speed * ForwardDragHigh;
	}
	else {
		speed -= DeltaTime * speed * ForwardDragLow;
	}

	TotalVelocity *= speed;

	FVector DesiredMovementThisFrame = TotalVelocity * DeltaTime;
	FHitResult Hit;
	SafeMoveUpdatedComponent(DesiredMovementThisFrame, currentRotation, true, Hit);

	// If we bumped into something, try to slide along it
	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
	}

	PitchInput = 0;
	YawInput = 0;
	Velocity = TotalVelocity;
};