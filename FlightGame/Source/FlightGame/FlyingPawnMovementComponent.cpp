// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingPawnMovementComponent.h"

void UFlyingPawnMovementComponent::AddPawnYawInput(float yaw) {
	YawInput += yaw;
};

void UFlyingPawnMovementComponent::AddPawnPitchInput(float pitch) {
	PitchInput += pitch;
};

void UFlyingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	PitchVelocity = PitchVelocity * FMath::Pow(0.96, DeltaTime / 0.015);
	PitchVelocity += PitchInput * DeltaTime * 900.0;
	PitchVelocity = FMath::Clamp(PitchVelocity, -600.0f, 600.0f);
	
	YawVelocity = YawVelocity * FMath::Pow(0.96, DeltaTime / 0.015);
	YawVelocity += YawInput * DeltaTime * 360.0;
	YawVelocity = FMath::Clamp(YawVelocity, -540.0f, 540.0f);

	FRotator yaw;
	yaw.Pitch = 0;
	yaw.Yaw = YawVelocity * DeltaTime;
	yaw.Roll = 0;

	FRotator pitch;
	pitch.Pitch = PitchVelocity * DeltaTime;
	pitch.Yaw = 0;
	pitch.Roll = 0;
	PitchInput = 0;
	YawInput = 0;


	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 450.0f;

	FRotator currentRotation = UpdatedComponent->GetComponentRotation();
	currentRotation += yaw;
	currentRotation += pitch;

	currentRotation.Pitch = FMath::Clamp(currentRotation.Pitch, -60.0f, 89.0f);
	currentRotation.Pitch *= FMath::Pow(0.96, DeltaTime / 0.015);
	DesiredMovementThisFrame = currentRotation.RotateVector(DesiredMovementThisFrame);

	if (true) {//!DesiredMovementThisFrame.IsNearlyZero())
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, currentRotation, true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
};