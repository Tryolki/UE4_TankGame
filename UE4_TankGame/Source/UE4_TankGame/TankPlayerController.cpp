// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "TankPlayerController.h"

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	auto ScreenLocation = FVector2D(viewportSizeX * CrossHairXLocation, viewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		if(GetLookVectorHitLocation(LookDirection, HitLocation))
			return true;
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitObject;
	auto LineStart = PlayerCameraManager->GetCameraLocation();
	FVector LineEnd = LineStart + LookDirection * visibleDistance;
	if (GetWorld()->LineTraceSingleByChannel
		(
			HitObject,
			LineStart,
			LineEnd,
			ECollisionChannel::ECC_Visibility
		))
	{
		HitLocation = HitObject.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldPosition;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldPosition,
		LookDirection);
}
