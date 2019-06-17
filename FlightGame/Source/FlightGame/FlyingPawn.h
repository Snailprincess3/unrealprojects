// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "FlyingPawn.generated.h"

UCLASS()
class FLIGHTGAME_API AFlyingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlyingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float val);

	void MoveRight(float val);

	void TiltRight(float val);

	void TiltDown(float val);

	void StartPrimaryFire();

	void EndPrimaryFire();

	class ABaseWeapon* CurrentWeapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	USceneComponent* AimMarker;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class UFlyingPawnMovementComponent* FlightMovementComponent;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|Weapon")
	void SetCurrentWeapon(class ABaseWeapon* newWeapon);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|Weapon")
	class ABaseWeapon* GetCurrentWeapon();


};
