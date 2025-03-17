// Aegis Protocol - DynamicTerrain.cpp
// Implements terrain-based movement, weapon accuracy, and armor effects.

#include "DynamicTerrain.h"
#include "MechCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

ADynamicTerrain::ADynamicTerrain()
{
    PrimaryActorTick.bCanEverTick = true;
    SpeedModifier = 1.0f;
    AccuracyModifier = 1.0f;
    ArmorEffectivenessModifier = 1.0f;
}

void ADynamicTerrain::BeginPlay()
{
    Super::BeginPlay();
}

void ADynamicTerrain::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADynamicTerrain::ApplyTerrainEffects(AMechCharacter* Mech, ETerrainType TerrainType)
{
    if (!Mech) return;

    switch (TerrainType)
    {
    case ETerrainType::Grassland:
        SpeedModifier = 1.0f; // Standard speed
        AccuracyModifier = 1.0f;
        ArmorEffectivenessModifier = 1.0f;
        break;

    case ETerrainType::Desert:
        SpeedModifier = 0.9f; // Slightly slower
        AccuracyModifier = 0.95f; // Slight aim penalty from sand
        ArmorEffectivenessModifier = 1.0f;
        break;

    case ETerrainType::Snow:
        SpeedModifier = 0.85f; // Slower movement
        AccuracyModifier = 0.9f; // Reduced accuracy due to visibility
        ArmorEffectivenessModifier = 1.1f; // Armor slightly more effective
        break;

    case ETerrainType::Swamp:
        SpeedModifier = 0.7f; // Very slow movement
        AccuracyModifier = 0.9f;
        ArmorEffectivenessModifier = 0.9f; // Armor less effective due to sinking
        break;

    case ETerrainType::Rocky:
        SpeedModifier = 0.95f; // Slightly slower
        AccuracyModifier = 1.05f; // Higher accuracy due to stable ground
        ArmorEffectivenessModifier = 1.0f;
        break;

    case ETerrainType::Urban:
        SpeedModifier = 1.0f; // No change
        AccuracyModifier = 1.0f;
        ArmorEffectivenessModifier = 1.0f;
        break;

    case ETerrainType::Water:
        SpeedModifier = 0.5f; // Very slow unless using hover/tracked legs
        AccuracyModifier = 0.85f;
        ArmorEffectivenessModifier = 1.0f;
        break;

    case ETerrainType::Mud:
        SpeedModifier = 0.75f; // Slower movement
        AccuracyModifier = 0.9f;
        ArmorEffectivenessModifier = 0.95f;
        break;
    }

    // Apply the modifiers to the mech
    Mech->SetSpeedMultiplier(SpeedModifier);
    Mech->SetAccuracyMultiplier(AccuracyModifier);
    Mech->SetArmorEffectiveness(ArmorEffectivenessModifier);

    UE_LOG(LogTemp, Log, TEXT("Applied Terrain Effect: Speed: %.2f, Accuracy: %.2f, Armor: %.2f"),
        SpeedModifier, AccuracyModifier, ArmorEffectivenessModifier);
}