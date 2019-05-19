// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"
#include "FlyingPathFollowingComponent.generated.h"

/**
 * 
 */
UCLASS()
class FLIGHTGAME_API UFlyingPathFollowingComponent : public UPathFollowingComponent
{
	GENERATED_BODY()

protected:

	//virtual void FollowPathSegment(float DeltaTime) override;

private:
	float TargetHeightOffset;

public:
	void SetTargetHeightOffset(float value);

	void ForcePathUpdate();

};
