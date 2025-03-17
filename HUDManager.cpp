// Aegis Protocol - HUDManager.cpp
// Implements the world map UI, battlefield selection, battle queueing, and enemy detection for minimap.

#include "HUDManager.h"
#include "Kismet/GameplayStatics.h"
#include "MultiplayerManager.h"
#include "Blueprint/UserWidget.h"

AHUDManager::AHUDManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AHUDManager::BeginPlay()
{
    Super::BeginPlay();
    InitializeBattlefields();
    DisplayWorldMap();
}

void AHUDManager::DrawHUD()
{
    Super::DrawHUD();
}

void AHUDManager::InitializeBattlefields()
{
    Battlefields = {
        // United Front (USA-Inspired) - 6 Battlefields
        { "Liberty Outpost", EFactionType::UnitedFront, 50000.0f, 1, false },
        { "Redwood Stronghold", EFactionType::UnitedFront, 50000.0f, 1, false },
        { "Fort Independence", EFactionType::UnitedFront, 100000.0f, 1, true },
        { "Skyline Crater", EFactionType::UnitedFront, 50000.0f, 1, false },
        { "Echo Ridge", EFactionType::UnitedFront, 50000.0f, 1, false },
        { "Titan Fields", EFactionType::UnitedFront, 50000.0f, 1, false },

        // Zephyr Dominion (Middle East-Inspired) - 7 Battlefields
        { "Desert Warlords' Keep", EFactionType::ZephyrDominion, 50000.0f, 2, false },
        { "Oil Refinery Alpha", EFactionType::ZephyrDominion, 50000.0f, 2, false },
        { "Sultan’s Command", EFactionType::ZephyrDominion, 100000.0f, 2, true },
        { "Mirage Flats", EFactionType::ZephyrDominion, 50000.0f, 2, false },
        { "Dune Fortress", EFactionType::ZephyrDominion, 50000.0f, 2, false },
        { "Nomad’s Crossing", EFactionType::ZephyrDominion, 50000.0f, 2, false },
        { "Solar Bastion", EFactionType::ZephyrDominion, 50000.0f, 2, false },

        // Volkov Imperium (Russia-Inspired) - 5 Battlefields
        { "Arctic Wolf Bastion", EFactionType::VolkovImperium, 50000.0f, 3, false },
        { "Volkov Military Base", EFactionType::VolkovImperium, 50000.0f, 3, false },
        { "Kremlin Fortress", EFactionType::VolkovImperium, 100000.0f, 3, true },
        { "Frozen Tundra Wastes", EFactionType::VolkovImperium, 50000.0f, 3, false },
        { "Iron Passage", EFactionType::VolkovImperium, 50000.0f, 3, false },

        // Phantom Syndicate (South Pacific-Inspired) - 6 Battlefields
        { "Jungle Phantom Hideout", EFactionType::PhantomSyndicate, 50000.0f, 4, false },
        { "Rainforest Tactical Hub", EFactionType::PhantomSyndicate, 50000.0f, 4, false },
        { "Shadow Overwatch", EFactionType::PhantomSyndicate, 100000.0f, 4, true },
        { "Viper’s Nest", EFactionType::PhantomSyndicate, 50000.0f, 4, false },
        { "Eclipse Basin", EFactionType::PhantomSyndicate, 50000.0f, 4, false },
        { "Sunken Temple Ruins", EFactionType::PhantomSyndicate, 50000.0f, 4, false }
    };
}

void AHUDManager::DisplayWorldMap()
{
    UE_LOG(LogTemp, Log, TEXT("Displaying World Map UI"));

    for (const FBattlefieldInfo& Battlefield : Battlefields)
    {
        FString Status = (Battlefield.bIsCapital) ? "Capital - High Priority" : "Standard Battlefield";
        UE_LOG(LogTemp, Log, TEXT("%s (%s) - %s - Health: %f - Controlled by Team %d"),
            *Battlefield.Name,
            *UEnum::GetValueAsString(Battlefield.Faction),
            *Status,
            Battlefield.Health,
            Battlefield.ControllingTeam);
    }
}

void AHUDManager::DisplayBattlefieldInfo(FString SelectedBattlefield)
{
    for (const FBattlefieldInfo& Battlefield : Battlefields)
    {
        if (Battlefield.Name == SelectedBattlefield)
        {
            UE_LOG(LogTemp, Log, TEXT("Selected Battlefield: %s"), *Battlefield.Name);
            UE_LOG(LogTemp, Log, TEXT("Faction: %s"), *UEnum::GetValueAsString(Battlefield.Faction));
            UE_LOG(LogTemp, Log, TEXT("Health: %f"), Battlefield.Health);
            UE_LOG(LogTemp, Log, TEXT("Controlling Team: %d"), Battlefield.ControllingTeam);
        }
    }
}

void AHUDManager::SelectBattlefield(FString BattlefieldName)
{
    UE_LOG(LogTemp, Log, TEXT("Battlefield %s selected!"), *BattlefieldName);
    QueueForBattle(BattlefieldName);
}

void AHUDManager::QueueForBattle(FString BattlefieldName)
{
    UE_LOG(LogTemp, Log, TEXT("Queuing team for battle at %s..."), *BattlefieldName);

    // Call MultiplayerManager to queue for a clan battle
    AMultiplayerManager* MultiplayerManager = Cast<AMultiplayerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMultiplayerManager::StaticClass()));

    if (MultiplayerManager)
    {
        MultiplayerManager->QueueClanForBattle(BattlefieldName);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("MultiplayerManager not found!"));
    }
}

// 🔥 NEW: Displays enemy positions on the minimap when detected
void AHUDManager::DisplayEnemyOnMinimap(FVector EnemyLocation)
{
    // Log enemy detection for debugging
    UE_LOG(LogTemp, Log, TEXT("Enemy detected on minimap at location: %s"), *EnemyLocation.ToString());

    // Ensure the HUD UI updates (this assumes a minimap widget exists)
    if (MinimapWidget)
    {
        MinimapWidget->AddEnemyMarker(EnemyLocation);
    }
}

// 🔥 NEW: Clears detected enemies from the minimap when they are no longer visible
void AHUDManager::ClearEnemyMarkers()
{
    if (MinimapWidget)
    {
        MinimapWidget->ClearEnemyMarkers();
    }
}