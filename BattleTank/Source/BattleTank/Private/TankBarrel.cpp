// Copyright 2017 Robert O'Quinn

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	// Move the barrel the right amount this frame given a max elevation speed
	// and the frame time.
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);
	auto elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto elevation = FMath::Clamp<float>(rawNewElevation, minElevationInDegrees, maxElevationInDegrees);

	SetRelativeRotation(FRotator(elevation, 0.0f, 0.0f));
}
