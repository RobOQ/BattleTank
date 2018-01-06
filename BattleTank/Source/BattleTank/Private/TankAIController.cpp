// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetAimingComponent();
	if (!ensure(AimingComponent))
	{
		return;
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
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
	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = GetAimingComponent();
	if (!ensure(AimingComponent))
	{
		return;
	}

	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
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

void ATankAIController::OnTankDeath()
{
	if (!GetPawn())
	{
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
}
