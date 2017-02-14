// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "TankTurret.h"
#include "TankBarrel.h"

void UTankTurret::SetBarrelReference(UTankBarrel * Barrel)
{
	BarrelComponent = Barrel;
}

void UTankTurret::Rotate(float RelativeTurretSpeed, float RelativeBarrelSpeed) 
{
	RelativeTurretSpeed = FMath::Clamp<float>(RelativeTurretSpeed, -1, +1);
	auto RelativeSpeed = RelativeTurretSpeed * MaxDegreePerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Yaw + RelativeSpeed;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(0.f, Elevation, 0.f));
	BarrelComponent->ElevateBarrel(RelativeBarrelSpeed);
}
