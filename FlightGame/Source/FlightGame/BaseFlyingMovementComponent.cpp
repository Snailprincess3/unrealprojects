// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFlyingMovementComponent.h"
#include "Components/SplineComponent.h"

void UBaseFlyingMovementComponent::Initialize() {
	MaxSpeed = 800;
}

void UBaseFlyingMovementComponent::SetUseAccelerationForPathing(bool useAcceleration) {
	bUseAccelerationForPaths = useAcceleration;
}

void UBaseFlyingMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	float currentSpeed;
	FVector currentDirection;
	FRotator currentRotation;
	FRotator desiredRotation;

	FVector DesiredMoveDirection = ConsumeInputVector();

	if (DesiredMoveDirection.IsNearlyZero()) {
		Velocity = Velocity * FMath::Pow(0.99, DeltaTime / 0.015);
		if (Velocity.IsNearlyZero()) {
			currentRotation = UpdatedComponent->GetComponentRotation();
		}
		else {
			Velocity.ToDirectionAndLength(currentDirection, currentSpeed);
			currentRotation = currentDirection.Rotation();
		}
	} else {
		Velocity.ToDirectionAndLength(currentDirection, currentSpeed);
		currentRotation = currentDirection.Rotation();
		desiredRotation = DesiredMoveDirection.Rotation();

		FRotator delta;
		delta.Pitch = GetMinimumAngleDelta(currentRotation.Pitch, desiredRotation.Pitch);
		delta.Yaw = GetMinimumAngleDelta(currentRotation.Yaw, desiredRotation.Yaw);
		delta.Roll = GetMinimumAngleDelta(currentRotation.Roll, desiredRotation.Roll);

		if (currentSpeed < MaxSpeed) {
			currentSpeed += 800 * DeltaTime;
		}

		float currentMaxSpeed = MaxSpeed;
		if ((FMath::Abs(delta.Pitch) > 70) || (FMath::Abs(delta.Yaw) > 70)) {
			currentMaxSpeed = 100;
		}
		currentSpeed = FMath::Min(currentMaxSpeed, currentSpeed);

		delta.Pitch = FMath::Clamp(delta.Pitch, -120 * DeltaTime, 120 * DeltaTime);
		delta.Yaw = FMath::Clamp(delta.Yaw, -120 * DeltaTime, 120 * DeltaTime);
		delta.Roll = FMath::Clamp(delta.Roll , -120 * DeltaTime, 120 * DeltaTime);

		currentRotation = currentRotation + delta;

		Velocity = currentRotation.Vector() * currentSpeed;
	}

	FVector DesiredMoveThisFrame = Velocity * DeltaTime;

	if (!DesiredMoveThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMoveThisFrame, currentRotation, true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMoveThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}

float UBaseFlyingMovementComponent::GetMinimumAngleDelta(float angle1, float angle2) {
	float diff = angle2 - angle1;

	if (diff < -180) {
		diff += 360;
	}

	if (diff > 180) {
		diff -= 360;
	}

	return diff;
}

void UBaseFlyingMovementComponent::RequestPathMove(const FVector& MoveInput)
{
	AddInputVector(MoveInput);
}

void UBaseFlyingMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	Velocity = MoveVelocity;
}

void UBaseFlyingMovementComponent::StopMovementKeepPathing() {
	Velocity.Z = 0;
}
