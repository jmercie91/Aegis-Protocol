//// Aegis Protocol - RadarHUD.h
// Implements UI radar system, tracking enemy positions, beacon status, and real-time detection updates.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RadarHUD.generated.h"

UCLASS()
class AEGISPROTOCOL_API ARadarHUD : public AHUD
{
    GENERATED_BODY()

public:
    ARadarHUD();

protected:
    virtual void BeginPlay() override;
    virtual void DrawHUD() override;

public:
    // Function to update detected enemies on radar
    UFUNCTION(BlueprintCallable, Category = "Radar")
    void UpdateEnemyPositions(const TArray<FVector>& EnemyLocations);

    // Function to update team member positions
    UFUNCTION(BlueprintCallable, Category = "Radar")
    void UpdateAllyPositions(const TArray<FVector>& AllyLocations);

    // Function to update beacon locations
    UFUNCTION(BlueprintCallable, Category = "Radar")
    void UpdateBeaconPositions(const TArray<FVector>& BeaconLocations);

    // Function to apply weather-based radar interference
    UFUNCTION(BlueprintCallable, Category = "Radar")
    void ApplyWeatherInterference(EWeatherCondition CurrentWeather);

private:
    // Stores enemy positions for rendering
    TArray<FVector> EnemyPositions;

    // Stores ally positions for rendering
    TArray<FVector> AllyPositions;

    // Stores beacon locations for rendering
    TArray<FVector> BeaconPositions;

    // Radar settings
    UPROPERTY(EditAnywhere, Category = "Radar Config")
    float RadarRadius;

    // Determines how much visibility is reduced during fog or storm
    float WeatherVisibilityModifier;

    // Function to render radar blips
    void RenderRadarElements();
};