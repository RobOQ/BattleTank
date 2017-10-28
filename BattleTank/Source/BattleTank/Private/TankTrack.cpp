// Copyright 2017 Robert O'Quinn

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *name, throttle);

	// TODO clamp actual throttle value so player can't drive faster than allowed
}
