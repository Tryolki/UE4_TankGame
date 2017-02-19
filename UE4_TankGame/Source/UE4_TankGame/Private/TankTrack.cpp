// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float value)
{
	auto ForceApplied = GetForwardVector() * value * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(
		ForceApplied,
		ForceLocation
	);
}
