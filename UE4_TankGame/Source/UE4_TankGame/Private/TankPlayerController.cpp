// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(AimingComponent)
		FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(HitLocation);
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
		return GetLookVectorHitLocation(LookDirection, HitLocation);
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
			ECollisionChannel::ECC_Camera
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

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	auto PossessedEnemy = Cast<ATank>(InPawn);
	if (!ensure(PossessedEnemy)) { return; }
	PossessedEnemy->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedObjectDeath);
}

void ATankPlayerController::OnPossedObjectDeath()
{
	StartSpectatingOnly();
}