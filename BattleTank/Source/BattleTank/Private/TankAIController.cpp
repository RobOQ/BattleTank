// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

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
	auto playerTank = GetPlayerTank();
	auto ourTank = Cast<ATank>(GetPawn());

	if (ensure(playerTank && ourTank))
	{
		// Move towards the player
		MoveToActor(playerTank, acceptanceRadius);

		// Aim towards the player
		ourTank->AimAt(playerTank->GetActorLocation());

		// TODO: Limit firing rate
		ourTank->Fire();
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATank* playerTank = nullptr;

	auto playerController = GetWorld()->GetFirstPlayerController();

	if (ensure(playerController))
	{
		auto playerPawn = playerController->GetPawn();

		if (ensure(playerPawn))
		{
			playerTank = Cast<ATank>(playerController->GetPawn());
		}
	}

	return playerTank;
}
