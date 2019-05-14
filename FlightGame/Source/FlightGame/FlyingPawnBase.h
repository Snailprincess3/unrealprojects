// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyingPawnBase.generated.h"

UCLASS()
class FLIGHTGAME_API AFlyingPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlyingPawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class UBaseFlyingMovementComponent* FlightMovementComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USplineComponent* CurrentSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USceneComponent* EntityRoot;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
};
