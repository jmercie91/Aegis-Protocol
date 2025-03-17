// Aegis Protocol - PerkSystem.cpp
// Implements class perks and nation perks, allowing players to swap perks in the Mech Creation Garage.

#include "PerkSystem.h"
#include "MechCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

APerkSystem::APerkSystem()
{
    PrimaryActorTick.bCanEverTick = false;
    bHasSelectedStandardPerk = false;
    bHasSelectedNationPerk = false;
}

void APerkSystem::BeginPlay()
{
    Super::BeginPlay();
}

// Set a standard perk (removes nation perk if already selected)
void APerkSystem::SetStandardPerk(AActor* Mech, EStandardPerk ChosenStandardPerk)
{
    AMechCharacter* MechCharacter = Cast<AMechCharacter>(Mech);
    if (!MechCharacter) return;

    if (bHasSelectedNationPerk)
    {
        RemoveSelectedPerk(Mech);
    }

    bHasSelectedStandardPerk = true;
    ActiveStandardPerk = ChosenStandardPerk;

    switch (ChosenStandardPerk)
    {
    case EStandardPerk::EmergencyEscape:
        MechCharacter->bHasEmergencyEscape = true;
        UE_LOG(LogTemp, Log, TEXT("Emergency Escape perk activated!"));
        break;

    case EStandardPerk::EnhancedRadar:
        MechCharacter->RadarRange += 0.15f * MechCharacter->RadarRange;
        UE_LOG(LogTemp, Log, TEXT("Radar range increased by 15%%!"));
        break;

    case EStandardPerk::ReinforcedArmor:
        MechCharacter->ArmorValue += 20.0f;
        UE_LOG(LogTemp, Log, TEXT("Armor reinforced by +20!"));
        break;

    case EStandardPerk::AmmoSpecialist:
        MechCharacter->AmmoCapacity += 10;
        UE_LOG(LogTemp, Log, TEXT("Ammo capacity increased by +10 rounds!"));
        break;

    case EStandardPerk::TargetingAssist:
        MechCharacter->TargetingAccuracy += 0.1f * MechCharacter->TargetingAccuracy;
        UE_LOG(LogTemp, Log, TEXT("Targeting accuracy improved by 10%%!"));
        break;

    case EStandardPerk::SpeedTuning:
        MechCharacter->MovementSpeed += 0.05f * MechCharacter->MovementSpeed;
        UE_LOG(LogTemp, Log, TEXT("Movement speed boosted by 5%%!"));
        break;
    }
}

// Set a nation perk (removes standard perk if already selected)
void APerkSystem::SetNationPerk(AActor* Mech, ENationPerk ChosenNationPerk)
{
    AMechCharacter* MechCharacter = Cast<AMechCharacter>(Mech);
    if (!MechCharacter) return;

    if (bHasSelectedStandardPerk)
    {
        RemoveSelectedPerk(Mech);
    }

    bHasSelectedNationPerk = true;
    ActiveNationPerk = ChosenNationPerk;

    switch (ChosenNationPerk)
    {
    case ENationPerk::UnitedFront:
        MechCharacter->VisibilityBoost = 0.15f;
        UE_LOG(LogTemp, Log, TEXT("USA Perk: Visibility increased by 15%% for gun targeting."));
        break;

    case ENationPerk::SandVeil:
        MechCharacter->EnvironmentalPenaltyReduction = 0.20f;
        UE_LOG(LogTemp, Log, TEXT("Middle East Perk: Sandstorm penalties reduced by 20%%."));
        break;

    case ENationPerk::IronUnion:
        MechCharacter->ColdResistance = 0.15f;
        UE_LOG(LogTemp, Log, TEXT("Russia Perk: Movement penalties in snow reduced by 15%%."));
        break;

    case ENationPerk::ShadowLegion:
        MechCharacter->AdaptiveCamouflage = true;
        UE_LOG(LogTemp, Log, TEXT("Jungle Perk: Adaptive camouflage enabled."));
        break;
    }
}

// Remove the currently selected perk (allows swapping)
void APerkSystem::RemoveSelectedPerk(AActor* Mech)
{
    AMechCharacter* MechCharacter = Cast<AMechCharacter>(Mech);
    if (!MechCharacter) return;

    if (bHasSelectedStandardPerk)
    {
        bHasSelectedStandardPerk = false;
        UE_LOG(LogTemp, Log, TEXT("Standard perk removed!"));
    }
    else if (bHasSelectedNationPerk)
    {
        bHasSelectedNationPerk = false;
        UE_LOG(LogTemp, Log, TEXT("Nation perk removed!"));
    }
}

// Get the selected standard perk
EStandardPerk APerkSystem::GetSelectedStandardPerk()
{
    return ActiveStandardPerk;
}

// Get the selected nation perk
ENationPerk APerkSystem::GetSelectedNationPerk()
{
    return ActiveNationPerk;
}