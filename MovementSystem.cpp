#include "MovementSystem.h"

AMovementSystem::AMovementSystem()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default leg type
    LegType = EMechLegType::Bipedal;

    // Initialize movement stats
    UpdateMovementStats();
}

void AMovementSystem::BeginPlay()
{
    Super::BeginPlay();
}

void AMovementSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMovementSystem::SetLegType(EMechLegType NewLegType)
{
    LegType = NewLegType;
    UpdateMovementStats();
}

void AMovementSystem::UpdateMovementStats()
{
    switch (LegType)
    {
    case EMechLegType::Bipedal:
        MaxSpeed = 600.0f;
        TurnRate = 70.0f;
        WeightCapacity = 100.0f;
        break;

    case EMechLegType::Quadruped:
        MaxSpeed = 500.0f;
        TurnRate = 80.0f;
        WeightCapacity = 150.0f;
        break;

    case EMechLegType::Hexapod:
        MaxSpeed = 400.0f;
        TurnRate = 60.0f;
        WeightCapacity = 200.0f;
        break;

    case EMechLegType::Tracked:
        MaxSpeed = 450.0f;
        TurnRate = 50.0f;
        WeightCapacity = 250.0f;
        break;

    case EMechLegType::Wheeled:
        MaxSpeed = 700.0f;
        TurnRate = 90.0f;
        WeightCapacity = 80.0f;
        break;
    }

    UE_LOG(LogTemp, Log, TEXT("Leg Type Set: %d | Max Speed: %.1f | Turn Rate: %.1f | Weight Capacity: %.1f"),
        static_cast<int32>(LegType), MaxSpeed, TurnRate, WeightCapacity);
}

float AMovementSystem::GetMaxSpeed() const
{
    return MaxSpeed;
}

float AMovementSystem::GetTurnRate() const
{
    return TurnRate;
}

float AMovementSystem::GetWeightCapacity() const
{
    return WeightCapacity;
}