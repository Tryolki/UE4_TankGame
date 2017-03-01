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

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

EFiringState UTankAimingComponent::GetFireState() const
{
	return EFiringState();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		AimingState = EFiringState::VE_Reloading;
	}
	else if(IsBarrelMove())
	{
		AimingState = EFiringState::VE_Aiming;
	}
	else
	{
		AimingState = EFiringState::VE_Locked;
	}
}

bool UTankAimingComponent::IsBarrelMove()
{
	if(!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.05);
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector & AimDirection)
{
	if (!ensure(Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	if (DeltaRotator.Yaw < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw, DeltaRotator.Pitch);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw, DeltaRotator.Pitch);
	}
}

void UTankAimingComponent::Fire()
{
	if (AimingState != EFiringState::VE_Reloading)
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

EFiringState UTankAimingComponent::UTankAimingComponent::GetFireState()
{
	return AimingState;
}