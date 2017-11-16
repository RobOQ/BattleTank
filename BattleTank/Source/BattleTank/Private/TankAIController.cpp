// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtPlayerTank();
}

void ATankAIController::AimAtPlayerTank()
{
	auto PlayerTank = GetPlayerTank();
	auto OurTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank && OurTank))
	{
		// Move towards the player
		MoveToActor(PlayerTank, acceptanceRadius);

		// Aim towards the player
		OurTank->AimAt(PlayerTank->GetActorLocation());

		// TODO: Limit firing rate
		OurTank->Fire();
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATank* PlayerTank = nullptr;

	auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (ensure(PlayerController))
	{
		auto PlayerPawn = PlayerController->GetPawn();

		if (ensure(PlayerPawn))
		{
			PlayerTank = Cast<ATank>(PlayerController->GetPawn());
		}
	}

	return PlayerTank;
}
