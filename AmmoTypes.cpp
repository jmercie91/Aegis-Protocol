// Aegis Protocol - AmmoTypes.cpp
// Implements different ammo types with modifiers and effects.

#include "AmmoTypes.h"

UAmmoTypes::UAmmoTypes() {}

// Returns damage modifier based on the ammo type
float UAmmoTypes::GetDamageModifier(EAmmoType AmmoType)
{
    switch (AmmoType)
    {
    case EAmmoType::Standard:
        return 1.0f; // No additional damage
    case EAmmoType::ArmorPiercing:
        return 1.25f; // Deals extra damage to armor
    case EAmmoType::Incendiary:
        return 1.1f; // Small damage boost, applies burn effect
    case EAmmoType::Explosive:
        return 1.3f; // AoE explosion damage modifier
    case EAmmoType::EMP:
        return 0.8f; // Lower base damage, but disables electronics
    case EAmmoType::Plasma:
        return 1.5f; // Strongest damage type, but lower fire rate
    default:
        return 1.0f;
    }
}

// Returns the description of the special effect for each ammo type
FString UAmmoTypes::GetAmmoEffect(EAmmoType AmmoType)
{
    switch (AmmoType)
    {
    case EAmmoType::Standard:
        return "Basic ammunition with no special properties.";
    case EAmmoType::ArmorPiercing:
        return "Ignores a portion of enemy armor, dealing increased damage.";
    case EAmmoType::Incendiary:
        return "Sets targets on fire, causing damage over time.";
    case EAmmoType::Explosive:
        return "Detonates on impact, dealing area damage.";
    case EAmmoType::EMP:
        return "Disrupts enemy electronics, disabling radar and HUD temporarily.";
    case EAmmoType::Plasma:
        return "Superheated energy rounds that deal extreme damage but have limited ammo.";
    default:
        return "Unknown ammo type.";
    }
}