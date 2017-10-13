// Copyright 2017 Robert O'Quinn

#include "TankPlayerController.h"
#include "Public/Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* controlledTank = GetControlledTank();

	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play possessing %s"), *(controlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play not possessing a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	// Get world location if linetrace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}
