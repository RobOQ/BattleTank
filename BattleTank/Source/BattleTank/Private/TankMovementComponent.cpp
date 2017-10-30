// Copyright 2017 Robert O'Quinn

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet)
	{
		return;
	}

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float throwValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throwValue: %f"), throwValue);

	if (!leftTrack || !rightTrack)
	{
		return;
	}

	leftTrack->SetThrottle(throwValue);
	rightTrack->SetThrottle(throwValue);

	// TODO prevent double speed from using double controls
}

