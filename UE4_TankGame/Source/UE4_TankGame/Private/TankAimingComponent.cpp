// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	if (!BarrelMeshComponent) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = BarrelMeshComponent->GetSocketLocation(FName("Projectile"));
	FVector EndLocation = WorldSpaceAim;
	auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		EndLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * component)
{
	BarrelMeshComponent = component;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector & AimDirection)
{
	auto BarrelRotator = BarrelMeshComponent->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("%s to %s"), *GetOwner()->GetName(), *AimAsRotator.ToString());
	auto DeltaRotator = AimAsRotator - BarrelRotator;

}