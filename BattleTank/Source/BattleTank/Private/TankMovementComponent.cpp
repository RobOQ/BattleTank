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
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto cosTheta = FVector::DotProduct(aiForwardIntention, tankForward);

	IntendMoveForward(cosTheta);
}

