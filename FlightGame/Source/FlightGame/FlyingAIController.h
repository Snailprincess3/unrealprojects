// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FlyingAIController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustomAINavigation, Log, All);
/**
 * 
 */
UCLASS()
class FLIGHTGAME_API AFlyingAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AFlyingAIController(const FObjectInitializer& ObjectInitializer);

private:

	/** Component used for moving along a path. */
	UPROPERTY(VisibleDefaultsOnly, Category = AI)
	class UFlyingPathFollowingComponent* FlyingPathFollowingComponent;

	FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath) override;


};
