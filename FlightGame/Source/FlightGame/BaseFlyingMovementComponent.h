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

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	virtual void RequestPathMove(const FVector& MoveInput) override;

	virtual void Initialize();

	void StopMovementKeepPathing();

private:

	float GetMinimumAngleDelta(float angle1, float angle2);

	AActor* LeaderActor;

	void PerformFollowMovement(float DeltaTime);

	void PerformInputBasedMovement(float DeltaTime);

	bool bFollowingLeader;

public:

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|PawnMovement")
	void SetLeader(AActor* leader);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|PawnMovement")
	void SetShouldFollowLeader(bool shouldFollow);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|PawnMovement")
	void SetFollowOffset(FVector newOffset);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|PawnMovement")
	void SetMaintainOrientation(bool shouldMaintainOrientation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	FVector FollowOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	bool bMirrorLeaderRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	bool bMaintainOrientation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	float MaxSpeed;

};
