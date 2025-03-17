// Aegis Protocol - MapManager.h
// Manages battle locations, control point system, and integrates Dynamic Terrain & Dynamic Weather.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicTerrain.h"
#include "DynamicWeather.h"
#include "MultiplayerManager.h"
#include "MapManager.generated.h"

UENUM(BlueprintType)
enum class ERegionType : uint8
{
    UnitedFront UMETA(DisplayName = "United Front"),   // USA-Inspired
    ZephyrDominion UMETA(DisplayName = "Zephyr Dominion"), // Middle East-Inspired
    VolkovImperium UMETA(DisplayName = "Volkov Imperium"), // Russia-Inspired
    PhantomSyndicate UMETA(DisplayName = "Phantom Syndicate") // South Pacific-Inspired
};

UENUM(BlueprintType)
enum class EWeatherCondition : uint8
{
    Clear UMETA(DisplayName = "Clear"),
    Rain UMETA(DisplayName = "Rain"),
    Storm UMETA(DisplayName = "Storm"),
    Snow UMETA(DisplayName = "Snow"),
    Sandstorm UMETA(DisplayName = "Sandstorm"),
    Fog UMETA(DisplayName = "Fog")
};

USTRUCT(BlueprintType)
struct FControlPoint
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point")
    ERegionType Region;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point")
    int32 ControllingTeam;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point")
    bool bIsCapital;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Point")
    EWeatherCondition DefaultWeather; // Weather assigned to this battlefield
};

UCLASS()
class AEGISPROTOCOL_API AMapManager : public AActor
{
    GENERATED_BODY()

public:
    AMapManager();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Battlefield Selection
    UFUNCTION(BlueprintCallable, Category = "Map")
    void LoadBattlefield(FString BattlefieldName);

    // Control Point Management
    UFUNCTION(BlueprintCallable, Category = "Control Point")
    void CaptureControlPoint(int32 TeamID, FString ControlPointName);

    UFUNCTION(BlueprintCallable, Category = "Control Point")
    void DamageControlPoint(FString ControlPointName, float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Control Point")
    void UpdateControlPointOwnership(FString ControlPointName, int32 NewOwnerTeam);

    UFUNCTION(BlueprintCallable, Category = "Victory")
    void CheckForVictoryCondition();

    // Dynamic Terrain Integration
    UFUNCTION(BlueprintCallable, Category = "Map")
    void ApplyTerrainToMech(class AMechCharacter* Mech);

    // Dynamic Weather Integration
    UFUNCTION(BlueprintCallable, Category = "Weather")
    void ApplyWeatherForBattlefield(FString BattlefieldName);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    TArray<FControlPoint> ControlPoints;

    UPROPERTY(EditAnywhere, Category = "Terrain")
    TSubclassOf<ADynamicTerrain> TerrainClass;

    UPROPERTY()
    ADynamicWeather* WeatherSystem;

    UPROPERTY()
    AMultiplayerManager* MultiplayerManager;

private:
    FString CurrentBattlefield;
    ADynamicTerrain* TerrainInstance;

    void InitializeMap();
    void UpdateWorldMapVisuals();
    ETerrainType GetTerrainTypeForBattlefield(FString Battlefield);
};