// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetAimingComponent();
	if (!ensure(AimingComponent))
	{
		return;
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtPlayerTank();
}

void ATankAIController::AimAtPlayerTank()
{
	auto PlayerTank = GetPlayerPawn();
	auto OurTank = GetPawn();

	if (!ensure(PlayerTank && OurTank))
	{
		return;
	}

	// Move towards the player
	MoveToActor(PlayerTank, acceptanceRadius);

	auto AimingComponent = GetAimingComponent();
	if (!ensure(AimingComponent))
	{
		return;
	}

	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
}
UTankAimingComponent* ATankAIController::GetAimingComponent() const
{
	return GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

APawn* ATankAIController::GetPlayerPawn() const
{
	APawn* PlayerPawn = nullptr;

	auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (ensure(PlayerController))
	{
		PlayerPawn = PlayerController->GetPawn();
	}

	return PlayerPawn;
}
