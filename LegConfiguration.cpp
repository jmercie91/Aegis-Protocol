#include "LegConfiguration.h"

ALegConfiguration::ALegConfiguration()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default leg type
    LegType = ELegType::StriderL2;  // Balanced Bipedal

    // Initialize leg stats
    UpdateLegStats();
}

void ALegConfiguration::BeginPlay()
{
    Super::BeginPlay();
}

void ALegConfiguration::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALegConfiguration::SetLegType(ELegType NewLegType)
{
    LegType = NewLegType;
    UpdateLegStats();
}

void ALegConfiguration::UpdateLegStats()
{
    switch (LegType)
    {
    case ELegType::FalconL1: // Light Bipedal
        SpeedModifier = 1.2f;
        TurnSpeed = 90.0f;
        WeightCapacity = 100.0f;
        break;

    case ELegType::StriderL2: // Balanced Bipedal
        SpeedModifier = 1.0f;
        TurnSpeed = 80.0f;
        WeightCapacity = 150.0f;
        break;

    case ELegType::JuggernautL3: // Heavy Bipedal
        SpeedModifier = 0.8f;
        TurnSpeed = 70.0f;
        WeightCapacity = 200.0f;
        break;

    case ELegType::CheetahQ1: // Light Quadruped
        SpeedModifier = 1.1f;
        TurnSpeed = 85.0f;
        WeightCapacity = 140.0f;
        break;

    case ELegType::SentinelQ2: // Balanced Quadruped
        SpeedModifier = 0.95f;
        TurnSpeed = 75.0f;
        WeightCapacity = 180.0f;
        break;

    case ELegType::ColossusQ3: // Heavy Quadruped
        SpeedModifier = 0.7f;
        TurnSpeed = 60.0f;
        WeightCapacity = 250.0f;
        break;

    case ELegType::WidowmakerH1: // Light Hexapod
        SpeedModifier = 0.9f;
        TurnSpeed = 65.0f;
        WeightCapacity = 220.0f;
        break;

    case ELegType::TitanH2: // Balanced Hexapod
        SpeedModifier = 0.75f;
        TurnSpeed = 55.0f;
        WeightCapacity = 280.0f;
        break;

    case ELegType::BehemothH3: // Heavy Hexapod
        SpeedModifier = 0.6f;
        TurnSpeed = 50.0f;
        WeightCapacity = 350.0f;
        break;

    case ELegType::ViperT1: // Light Tracked
        SpeedModifier = 1.05f;
        TurnSpeed = 50.0f;
        WeightCapacity = 230.0f;
        break;

    case ELegType::GoliathT2: // Heavy Tracked
        SpeedModifier = 0.8f;
        TurnSpeed = 40.0f;
        WeightCapacity = 300.0f;
        break;

    case ELegType::RaptorW1: // Light Wheeled
        SpeedModifier = 1.4f;
        TurnSpeed = 100.0f;
        WeightCapacity = 90.0f;
        break;

    case ELegType::NomadW2: // All-Terrain Wheeled
        SpeedModifier = 1.2f;
        TurnSpeed = 80.0f;
        WeightCapacity = 110.0f;
        break;
    }

    UE_LOG(LogTemp, Log, TEXT("Leg Type Set: %d | Speed Modifier: %.2f | Turn Speed: %.1f | Weight Capacity: %.1f"),
        static_cast<int32>(LegType), SpeedModifier, TurnSpeed, WeightCapacity);
}

float ALegConfiguration::GetSpeedModifier() const
{
    return SpeedModifier;
}

float ALegConfiguration::GetTurnSpeed() const
{
    return TurnSpeed;
}

float ALegConfiguration::GetWeightCapacity() const
{
    return WeightCapacity;
}