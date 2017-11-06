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
	if (!ensure(leftTrack && rightTrack))
	{
		return;
	}

	leftTrack->SetThrottle(throwValue);
	rightTrack->SetThrottle(throwValue);
}

void UTankMovementComponent::IntendTurnRight(float throwValue)
{
	if (!ensure(leftTrack && rightTrack))
	{
		return;
	}

	leftTrack->SetThrottle(throwValue);
	rightTrack->SetThrottle(-throwValue);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto forwardThrow = FVector::DotProduct(aiForwardIntention, tankForward);
	IntendMoveForward(forwardThrow);

	auto rightThrow = FVector::CrossProduct(tankForward, aiForwardIntention).Z;
	IntendTurnRight(rightThrow);
}

