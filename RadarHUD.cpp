// Aegis Protocol - RadarHUD.cpp
// Implements UI radar system, rendering enemy, ally, and beacon positions, and adjusting visibility based on weather.

#include "RadarHUD.h"
#include "Kismet/GameplayStatics.h"
#include "DynamicWeather.h"

ARadarHUD::ARadarHUD()
{
    PrimaryActorTick.bCanEverTick = true;
    RadarRadius = 5000.0f; // Default radar detection range
    WeatherVisibilityModifier = 1.0f; // No reduction by default
}

void ARadarHUD::BeginPlay()
{
    Super::BeginPlay();
}

void ARadarHUD::DrawHUD()
{
    Super::DrawHUD();
    RenderRadarElements();
}

void ARadarHUD::UpdateEnemyPositions(const TArray<FVector>& EnemyLocations)
{
    EnemyPositions = EnemyLocations;
}

void ARadarHUD::UpdateAllyPositions(const TArray<FVector>& AllyLocations)
{
    AllyPositions = AllyLocations;
}

void ARadarHUD::UpdateBeaconPositions(const TArray<FVector>& BeaconLocations)
{
    BeaconPositions = BeaconLocations;
}

void ARadarHUD::ApplyWeatherInterference(EWeatherCondition CurrentWeather)
{
    switch (CurrentWeather)
    {
    case EWeatherCondition::Fog:
        WeatherVisibilityModifier = 0.7f; // 30% reduction in radar effectiveness
        break;
    case EWeatherCondition::Storm:
        WeatherVisibilityModifier = 0.6f; // 40% reduction in visibility
        break;
    case EWeatherCondition::Sandstorm:
        WeatherVisibilityModifier = 0.5f; // 50% reduction in visibility
        break;
    default:
        WeatherVisibilityModifier = 1.0f; // Clear weather, full visibility
        break;
    }

    UE_LOG(LogTemp, Log, TEXT("Radar visibility modified due to weather: %f"), WeatherVisibilityModifier);
}

void ARadarHUD::RenderRadarElements()
{
    for (const FVector& Enemy : EnemyPositions)
    {
        FVector2D ScreenPosition;
        if (Project(Enemy, ScreenPosition))
        {
            DrawRect(FLinearColor::Red, ScreenPosition.X, ScreenPosition.Y, 10.0f, 10.0f);
        }
    }

    for (const FVector& Ally : AllyPositions)
    {
        FVector2D ScreenPosition;
        if (Project(Ally, ScreenPosition))
        {
            DrawRect(FLinearColor::Green, ScreenPosition.X, ScreenPosition.Y, 10.0f, 10.0f);
        }
    }

    for (const FVector& Beacon : BeaconPositions)
    {
        FVector2D ScreenPosition;
        if (Project(Beacon, ScreenPosition))
        {
            DrawRect(FLinearColor::Blue, ScreenPosition.X, ScreenPosition.Y, 12.0f, 12.0f);
        }
    }
}