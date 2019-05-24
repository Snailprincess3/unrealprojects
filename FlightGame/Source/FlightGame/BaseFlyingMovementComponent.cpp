// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFlyingMovementComponent.h"
#include "Components/SplineComponent.h"

void UBaseFlyingMovementComponent::Initialize() {
	FollowOffset.X = 0;
	FollowOffset.Y = 100;
	FollowOffset.Z = 0;

	MaxSpeed = 800;
	bUseAccelerationForPaths = true;
}

void UBaseFlyingMovementComponent::SetLeader(AActor* newLeader) {
	LeaderActor = newLeader;
}

void UBaseFlyingMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (!bFollowingLeader || LeaderActor == NULL) {
		PerformInputBasedMovement(DeltaTime);
	}
	else {
		PerformFollowMovement(DeltaTime);
	}
}

void UBaseFlyingMovementComponent::PerformFollowMovement(float DeltaTime) {
	ConsumeInputVector();
	
	FVector currentPos = UpdatedComponent->GetComponentLocation();
	FVector leaderPos = LeaderActor->GetActorLocation();
	FVector targetPos;
	float targetDistance;
	if (bMaintainOrientation) {
		FRotator leaderOrientation = LeaderActor->GetActorRotation();

		targetPos = leaderPos + leaderOrientation.RotateVector(FollowOffset);
		targetDistance = 0;
	}
	else {
		targetPos = leaderPos;
		FVector vec;
		FollowOffset.ToDirectionAndLength(vec, targetDistance);
	}

	FVector diff = targetPos - currentPos;
	float dist;
	FVector direction;
	diff.ToDirectionAndLength(direction, dist);

	FVector desiredDirection;

	float delta = dist - targetDistance;
	delta = FMath::Clamp(delta, -MaxSpeed * DeltaTime, MaxSpeed * DeltaTime);

	FVector DesiredMoveThisFrame = direction * delta;
	FRotator newRotation = direction.ToOrientationRotator();

	FHitResult Hit;
	SafeMoveUpdatedComponent(DesiredMoveThisFrame, newRotation, true, Hit);

	// If we bumped into something, try to slide along it
	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(DesiredMoveThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
	}

}

void UBaseFlyingMovementComponent::SetFollowOffset(FVector newOffset) {
	FollowOffset = newOffset;
}

void UBaseFlyingMovementComponent::SetMaintainOrientation(bool shouldMaintainOrientation) {
	bMaintainOrientation = shouldMaintainOrientation;
}

void UBaseFlyingMovementComponent::SetShouldFollowLeader(bool shouldFollow) {
	bFollowingLeader = shouldFollow;
}

void UBaseFlyingMovementComponent::PerformInputBasedMovement(float DeltaTime) {
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
	//Velocity = MoveVelocity;
	bUseAccelerationForPaths = true;
}

void UBaseFlyingMovementComponent::StopMovementKeepPathing() {
	Velocity.Z = 0;
}
