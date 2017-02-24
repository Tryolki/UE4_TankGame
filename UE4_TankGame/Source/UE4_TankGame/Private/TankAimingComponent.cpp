// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4_TankGame.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Tank.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimingComponent::Initialize(UTankBarrel * TankBarrel, UTankTurret * TankTurret)
{
	Barrel = TankBarrel;
	Turret = TankTurret;
	Turret->SetBarrelReference(Barrel);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector EndLocation = HitLocation;
	auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		EndLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector & AimDirection)
{
	if (!ensure(Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Turret->Rotate(DeltaRotator.Yaw, DeltaRotator.Pitch);
}

void UTankAimingComponent::Fire()
{
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds)
	{
		if (!Barrel) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(5000);
		LastFireTime = FPlatformTime::Seconds();
	}

}