// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankAimingComponent;
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditanyWhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditanyWhere)
	float CrossHairYLocation = 0.3f;
	UPROPERTY(VisibleAnywhere)
	float visibleDistance = 1000000.f;
	void Tick(float DeltaTime) override;

	void BeginPlay() override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector & HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	virtual void SetPawn(APawn* InPawn) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);

	UFUNCTION()
	void OnPossedObjectDeath();
};
