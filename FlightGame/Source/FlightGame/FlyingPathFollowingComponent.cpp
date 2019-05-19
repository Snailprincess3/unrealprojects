// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingPathFollowingComponent.h"

void UFlyingPathFollowingComponent::SetTargetHeightOffset(float value) {
	TargetHeightOffset = value;
}

void UFlyingPathFollowingComponent::ForcePathUpdate() {
	SetMoveSegment(MoveSegmentStartIndex);
}

/*
void UFlyingPathFollowingComponent::FollowPathSegment(float DeltaTime)
{
	if (!Path.IsValid() || MovementComp == nullptr)
	{
		return;
	}

	const FVector CurrentLocation = MovementComp->GetActorFeetLocation();
	const FVector CurrentTarget = GetCurrentTargetLocation();

	// set to false by default, we will set set this back to true if appropriate
	bIsDecelerating = false;

	float offset = float(MoveSegmentEndIndex) / Path.Get()->GetPathPoints().Num() * TargetHeightOffset;

	CurrentMoveInput = (CurrentTarget - CurrentLocation);
	CurrentMoveInput.Z += offset;
	CurrentMoveInput = CurrentMoveInput.GetSafeNormal();

	if (MoveSegmentStartIndex >= DecelerationSegmentIndex)
	{
		const FVector PathEnd = Path->GetEndLocation();
		const float DistToEndSq = FVector::DistSquared(CurrentLocation, PathEnd);
		const bool bShouldDecelerate = DistToEndSq < FMath::Square(CachedBrakingDistance);
		if (bShouldDecelerate)
		{
			bIsDecelerating = true;

			const float SpeedPct = FMath::Clamp(FMath::Sqrt(DistToEndSq) / CachedBrakingDistance, 0.0f, 1.0f);
			CurrentMoveInput *= SpeedPct;
		}
	}

	PostProcessMove.ExecuteIfBound(this, CurrentMoveInput);
	MovementComp->RequestPathMove(CurrentMoveInput);
}*/
