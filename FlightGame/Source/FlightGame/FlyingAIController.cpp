// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingAIController.h"
#include "FlyingPathFollowingComponent.h"
#include "VisualLogger/VisualLoggerTypes.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogCustomAINavigation);

AFlyingAIController::AFlyingAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	FlyingPathFollowingComponent = CreateDefaultSubobject<UFlyingPathFollowingComponent>(TEXT("FlyingPathFollowingComponent"));
	FlyingPathFollowingComponent->OnRequestFinished.AddUObject(this, &AFlyingAIController::OnMoveCompleted);
	SetPathFollowingComponent(FlyingPathFollowingComponent);
}

FPathFollowingRequestResult AFlyingAIController::MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath) {
	float targetZ = MoveRequest.GetGoalLocation().Z;
	float currentZ = GetPawn()->GetActorLocation().Z;
	FPathFollowingRequestResult result;
	FNavPathSharedPtr Path;
	result = Super::MoveTo(MoveRequest, &Path);
	float pathZ = MoveRequest.GetGoalLocation().Z;
	float offset = targetZ - pathZ;
	float startOffset = currentZ - pathZ;
	offset = offset - startOffset;
	UE_LOG(LogTemp, Log, TEXT("current z %d"), currentZ);
	if (!Path.IsValid() || !Path.Get()->IsValid()) {
		return result;
	}
	int num = Path.Get()->GetPathPoints().Num();
	for (int i = 0; i < Path.Get()->GetPathPoints().Num(); i++) {
		Path.Get()->GetPathPoints()[i].Location.Z += startOffset + offset * float(i) / (num - 1);
	}

	UFlyingPathFollowingComponent* pathFollower = (UFlyingPathFollowingComponent*)GetPathFollowingComponent();
	if (pathFollower->bIsActive) {
		if (OutPath) {
			*OutPath = Path;
		}
	}
	pathFollower->ForcePathUpdate();

	return result;
}

