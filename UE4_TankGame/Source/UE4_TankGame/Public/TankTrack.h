// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class UE4_TANKGAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float value);
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000;

	UFUNCTION(BlueprintCallable, Category = HitCollision)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
private:
	UTankTrack();
	virtual void BeginPlay() override;
	void ApplySidewaysForce();
	void DriveTrack();
	float CurrentThrottle = 0.f;
};
