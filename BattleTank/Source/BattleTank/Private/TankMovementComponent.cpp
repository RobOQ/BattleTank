// Copyright 2017 Robert O'Quinn

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float throwValue)
{
	if (!leftTrack || !rightTrack)
	{
		return;
	}

	leftTrack->SetThrottle(throwValue);
	rightTrack->SetThrottle(throwValue);

	// TODO prevent double speed from using double controls
}

void UTankMovementComponent::IntendTurnRight(float throwValue)
{
	if (!leftTrack || !rightTrack)
	{
		return;
	}

	leftTrack->SetThrottle(throwValue);
	rightTrack->SetThrottle(-throwValue);

	// TODO prevent double speed from using double controls
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto tankName = GetOwner()->GetName();
	auto moveVelocityString = MoveVelocity.ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s: MoveVelocity = %s"), *tankName, *moveVelocityString);
}

