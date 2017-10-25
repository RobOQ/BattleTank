// Copyright 2017 Robert O'Quinn

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetBarrelReference(UTankBarrel* barrelToSet)
{
	tankAimingComponent->SetBarrelReference(barrelToSet);
}

void ATank::SetTurretReference(UTankTurret* turretToSet)
{
	tankAimingComponent->SetTurretReference(turretToSet);
}

void ATank::Fire()
{
	auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: FIRE!"), time);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

