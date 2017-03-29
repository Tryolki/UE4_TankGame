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

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (AmmoCount <= 0)
	{
		AimingState = EFiringState::VE_OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
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
	if(!ensure(Towers[activeTowerIndex].Barrel)) { return false; }
	auto BarrelForward = Towers[activeTowerIndex].Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.05);
}
void UTankAimingComponent::Initialize(UTankBarrel * TankBarrel, UTankTurret * TankTurret)
{
	Barrel = TankBarrel;
	Turret = TankTurret;
	Turret->SetBarrelReference(Barrel);
}

void UTankAimingComponent::AddTower(FTower Tower)
{
	Towers.Add(Tower);
}

void UTankAimingComponent::ChangeWeapon(UTankBarrel * TankBarrel, UTankTurret * TankTurret)
{	
	if (activeTowerIndex > Towers.Num()-1)
	{
		activeTowerIndex = 0;
	}
	else {
		activeTowerIndex++;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Towers[activeTowerIndex].Barrel) || !ensure(Towers[activeTowerIndex].Turret)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Towers[activeTowerIndex].Barrel->GetSocketLocation(FName("Projectile"));
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
	if (!ensure(Towers[activeTowerIndex].Turret)) { return; }
	auto BarrelRotator = Towers[activeTowerIndex].Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Towers[activeTowerIndex].Turret->Rotate(DeltaRotator.Yaw, DeltaRotator.Pitch);
	}
	else {
		Towers[activeTowerIndex].Turret->Rotate(-DeltaRotator.Yaw, DeltaRotator.Pitch);
	}
}

void UTankAimingComponent::Fire()
{
	if (AimingState != EFiringState::VE_Reloading && AimingState != EFiringState::VE_OutOfAmmo)
	{
		if (!ensure(Towers[activeTowerIndex].Barrel)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			Towers[activeTowerIndex].ProjectileBlueprint,
			Towers[activeTowerIndex].Barrel->GetSocketLocation(FName("Projectile")),
			Towers[activeTowerIndex].Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(5000);
		LastFireTime = FPlatformTime::Seconds();
		AmmoCount--;
	}

}

EFiringState UTankAimingComponent::GetFireState() const
{
	return AimingState;
}
int UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}
