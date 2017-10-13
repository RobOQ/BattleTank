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
