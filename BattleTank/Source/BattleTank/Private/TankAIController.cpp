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

	if (playerTank && ourTank)
	{
		// TODO: Move towards the player
		
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

	if (playerController)
	{
		auto playerPawn = playerController->GetPawn();

		if (playerPawn)
		{
			playerTank = Cast<ATank>(playerController->GetPawn());
		}
	}

	return playerTank;
}
