// Copyright 2017 Robert O'Quinn

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);

	auto rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto rawNewRotation = RelativeRotation.Yaw + rotationChange;
	auto rotation = FMath::Clamp<float>(rawNewRotation, minRotationInDegrees, maxRotationInDegrees);

	SetRelativeRotation(FRotator(0.0f, rotation, 0.0f));
}
