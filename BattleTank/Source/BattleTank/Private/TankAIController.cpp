// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* playerTank = GetPlayerTank();

	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController player tank is %s"), *(playerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController could not find player tank"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtPlayerTank();
}

void ATankAIController::AimAtPlayerTank()
{
	auto playerTank = GetPlayerTank();
	auto ourTank = GetControlledTank();

	if (playerTank && ourTank)
	{
		// TODO: Move towards the player
		
		// Aim towards the player
		ourTank->AimAt(playerTank->GetActorLocation());

		// TODO: Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerController = GetWorld()->GetFirstPlayerController();

	if (playerController)
	{
		auto playerPawn = playerController->GetPawn();

		if (playerPawn)
		{
			auto playerTank = Cast<ATank>(playerController->GetPawn());
			return playerTank;
		}
	}

	return nullptr;
}
