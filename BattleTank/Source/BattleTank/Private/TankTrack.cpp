// Copyright 2017 Robert O'Quinn

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	throttle = FMath::Clamp(throttle, -1.0f, 1.0f);
	auto forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);

	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s forceApplied: %s"), *name, *forceApplied.ToString());
}
