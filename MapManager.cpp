// Aegis Protocol - MapManager.cpp
// Implements battle location management, control point capture, and integrates Dynamic Terrain & Dynamic Weather.

#include "MapManager.h"
#include "DynamicTerrain.h"
#include "DynamicWeather.h"
#include "MechCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "HUDManager.h"
#include "MultiplayerManager.h"

AMapManager::AMapManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMapManager::BeginPlay()
{
    Super::BeginPlay();
    InitializeMap();

    // Locate Dynamic Weather system in the world
    WeatherSystem = Cast<ADynamicWeather>(UGameplayStatics::GetActorOfClass(GetWorld(), ADynamicWeather::StaticClass()));
    MultiplayerManager = Cast<AMultiplayerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMultiplayerManager::StaticClass()));
}

void AMapManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMapManager::InitializeMap()
{
    ControlPoints = {
        // United Front (USA-Inspired) - 5 Battlefields
        { "Liberty Outpost", ERegionType::UnitedFront, 50000.0f, 1, false, EWeatherCondition::Clear },
        { "Redwood Stronghold", ERegionType::UnitedFront, 50000.0f, 1, false, EWeatherCondition::Rain },
        { "Fort Independence", ERegionType::UnitedFront, 100000.0f, 1, true, EWeatherCondition::Clear },
        { "Skyline Crater", ERegionType::UnitedFront, 50000.0f, 1, false, EWeatherCondition::Storm },
        { "Titan Fields", ERegionType::UnitedFront, 50000.0f, 1, false, EWeatherCondition::Fog },

        // Zephyr Dominion (Middle East-Inspired) - 7 Battlefields
        { "Desert Warlords' Keep", ERegionType::ZephyrDominion, 50000.0f, 2, false, EWeatherCondition::Sandstorm },
        { "Oil Refinery Alpha", ERegionType::ZephyrDominion, 50000.0f, 2, false, EWeatherCondition::Clear },
        { "Sultan’s Command", ERegionType::ZephyrDominion, 100000.0f, 2, true, EWeatherCondition::Clear },
        { "Mirage Flats", ERegionType::ZephyrDominion, 50000.0f, 2, false, EWeatherCondition::Sandstorm },
        { "Dune Fortress", ERegionType::ZephyrDominion, 50000.0f, 2, false, EWeatherCondition::Clear },
        { "Nomad’s Crossing", ERegionType::ZephyrDominion, 50000.0f, 2, false, EWeatherCondition::Fog },
        { "Solar Bastion", ERegionType::ZephyrDominion, 50000.0f, 2, false, EWeatherCondition::Storm },

        // Volkov Imperium (Russia-Inspired) - 6 Battlefields
        { "Arctic Wolf Bastion", ERegionType::VolkovImperium, 50000.0f, 3, false, EWeatherCondition::Snow },
        { "Volkov Military Base", ERegionType::VolkovImperium, 50000.0f, 3, false, EWeatherCondition::Storm },
        { "Kremlin Fortress", ERegionType::VolkovImperium, 100000.0f, 3, true, EWeatherCondition::Clear },
        { "Frozen Tundra Wastes", ERegionType::VolkovImperium, 50000.0f, 3, false, EWeatherCondition::Snow },
        { "Iron Passage", ERegionType::VolkovImperium, 50000.0f, 3, false, EWeatherCondition::Fog },
        { "Blizzard Fortress", ERegionType::VolkovImperium, 50000.0f, 3, false, EWeatherCondition::Snow },

        // Phantom Syndicate (South Pacific-Inspired) - 6 Battlefields
        { "Jungle Phantom Hideout", ERegionType::PhantomSyndicate, 50000.0f, 4, false, EWeatherCondition::Rain },
        { "Rainforest Tactical Hub", ERegionType::PhantomSyndicate, 50000.0f, 4, false, EWeatherCondition::Fog },
        { "Shadow Overwatch", ERegionType::PhantomSyndicate, 100000.0f, 4, true, EWeatherCondition::Clear },
        { "Viper’s Nest", ERegionType::PhantomSyndicate, 50000.0f, 4, false, EWeatherCondition::Storm },
        { "Eclipse Basin", ERegionType::PhantomSyndicate, 50000.0f, 4, false, EWeatherCondition::Rain },
        { "Sunken Temple Ruins", ERegionType::PhantomSyndicate, 50000.0f, 4, false, EWeatherCondition::Fog }
    };

    UE_LOG(LogTemp, Log, TEXT("Map initialized with control points and weather conditions."));
}

void AMapManager::LoadBattlefield(FString BattlefieldName)
{
    CurrentBattlefield = BattlefieldName;
    UE_LOG(LogTemp, Log, TEXT("Loaded Battlefield: %s"), *CurrentBattlefield);

    if (TerrainInstance)
    {
        TerrainInstance->Destroy();
    }

    if (TerrainClass)
    {
        FActorSpawnParameters SpawnParams;
        TerrainInstance = GetWorld()->SpawnActor<ADynamicTerrain>(TerrainClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    }

    // Apply weather conditions dynamically across all clients
    ApplyWeatherForBattlefield(BattlefieldName);
    if (MultiplayerManager)
    {
        MultiplayerManager->SyncWeatherForAllPlayers(BattlefieldName);
    }
}

void AMapManager::ApplyTerrainToMech(AMechCharacter* Mech)
{
    if (!Mech || !TerrainInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("Mech or Terrain instance is invalid!"));
        return;
    }

    ETerrainType Terrain = GetTerrainTypeForBattlefield(CurrentBattlefield);
    TerrainInstance->ApplyTerrainEffects(Mech, Terrain);
}

void AMapManager::ApplyWeatherForBattlefield(FString BattlefieldName)
{
    if (!WeatherSystem) return;

    for (const FControlPoint& Point : ControlPoints)
    {
        if (Point.Name == BattlefieldName)
        {
            UE_LOG(LogTemp, Log, TEXT("Applying weather: %d for %s"), (int32)Point.DefaultWeather, *BattlefieldName);
            WeatherSystem->ChangeWeather(Point.DefaultWeather);
            break;
        }
    }
}

ETerrainType AMapManager::GetTerrainTypeForBattlefield(FString Battlefield)
{
    if (Battlefield.Contains("Desert")) return ETerrainType::Desert;
    if (Battlefield.Contains("Snow")) return ETerrainType::Snow;
    if (Battlefield.Contains("Swamp")) return ETerrainType::Swamp;
    if (Battlefield.Contains("Rocky")) return ETerrainType::Rocky;
    if (Battlefield.Contains("Urban")) return ETerrainType::Urban;
    return ETerrainType::Grassland;
}