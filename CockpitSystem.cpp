#include "CockpitSystem.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Constructor to initialize default values
UCockpitSystem::UCockpitSystem()
{
	// Default values
	Health = 100.0f;
	Speed = 100.0f;
	Armor = 50.0f;
	Energy = 100.0f;
	CockpitSize = ECockpitSize::Medium;
	PlayerID = -1;
	TeamID = -1;

	// Default modifiers
	CockpitModifiers.RadarBoost = 0.0f;
	CockpitModifiers.VisionRange = 0.0f;
	CockpitModifiers.StealthLevel = 0.0f;
	CockpitModifiers.SpeedBoost = 0.0f;
	CockpitModifiers.HealthBoost = 0.0f;
	CockpitModifiers.ExplosiveDamageBoost = 0.0f;
}

// Initialize the cockpit system with player ID, team ID, and cockpit size
void UCockpitSystem::InitializeCockpit(int32 InPlayerID, int32 InTeamID, ECockpitSize InCockpitSize)
{
	PlayerID = InPlayerID;
	TeamID = InTeamID;
	CockpitSize = InCockpitSize;

	// Update stats and modifiers based on the cockpit size
	UpdateCockpitStats();
}

// Update the cockpit's stats (health, speed, armor, energy) based on the cockpit size
void UCockpitSystem::UpdateCockpitStats()
{
	switch (CockpitSize)
	{
	case ECockpitSize::Assault:
		Health = 120.0f;
		Speed = 90.0f;
		Armor = 70.0f;
		Energy = 100.0f;
		CockpitModifiers.SpeedBoost = 10.0f; // Speed boost for Assault cockpits
		CockpitModifiers.HealthBoost = 10.0f; // Health boost for Assault cockpits
		break;

	case ECockpitSize::Scout:
		Health = 60.0f;
		Speed = 130.0f;
		Armor = 30.0f;
		Energy = 80.0f;
		CockpitModifiers.SpeedBoost = 25.0f; // Scout cockpits are faster
		break;

	case ECockpitSize::Heavy:
		Health = 150.0f;
		Speed = 70.0f;
		Armor = 100.0f;
		Energy = 120.0f;
		CockpitModifiers.HealthBoost = 20.0f; // Extra health for Heavy cockpits
		break;

	case ECockpitSize::Demolition:
		Health = 140.0f;
		Speed = 75.0f;
		Armor = 90.0f;
		Energy = 130.0f;
		CockpitModifiers.ExplosiveDamageBoost = 25.0f; // Increased explosive damage for Demolition
		break;

	case ECockpitSize::Espionage:
		Health = 50.0f;
		Speed = 120.0f; // Espionage cockpit moves faster
		Armor = 20.0f;
		Energy = 100.0f;
		CockpitModifiers.SpeedBoost = 15.0f; // Increased speed for espionage
		break;

	case ECockpitSize::Artillery:
		Health = 180.0f;
		Speed = 50.0f;
		Armor = 110.0f;
		Energy = 150.0f;
		CockpitModifiers.ExplosiveDamageBoost = 20.0f; // Artillery cockpit has more explosive damage
		break;

	case ECockpitSize::Support:
		Health = 120.0f;
		Speed = 90.0f;
		Armor = 60.0f;
		Energy = 110.0f;
		CockpitModifiers.RadarBoost = 15.0f; // Support cockpits boost radar range
		CockpitModifiers.VisionRange = 5.0f; // Enhanced vision range for Support
		break;

	case ECockpitSize::Stealth:
		Health = 50.0f;
		Speed = 130.0f;
		Armor = 30.0f;
		Energy = 60.0f;
		CockpitModifiers.VisionRange = 10.0f; // Enhanced vision range for Support
		CockpitModifiers.SpeedBoost = 10.0f; // Increased speed for espionage
		break;

	case ECockpitSize::XLarge:
		Health = 200.0f;
		Speed = 60.0f;
		Armor = 120.0f;
		Energy = 150.0f;
		CockpitModifiers.RadarBoost = 15.0f; // Increased radar boost for XL cockpits
		break;

	case ECockpitSize::Small:
		Health = 75.0f;
		Speed = 120.0f;
		Armor = 40.0f;
		Energy = 80.0f;
		CockpitModifiers.RadarBoost = 10.0f; // Small cockpits have better radar detection
		CockpitModifiers.SpeedBoost = 10.0f; // Increased speed for espionage
		break;

	case ECockpitSize::Medium:
		Health = 100.0f;
		Speed = 100.0f;
		Armor = 50.0f;
		Energy = 100.0f;
		CockpitModifiers.RadarBoost = 5.0f; // Moderate radar boost for medium cockpits
		CockpitModifiers.VisionRange = 10.0f; // Vision boost for medium cockpits
		break;

	case ECockpitSize::Large:
		Health = 150.0f;
		Speed = 80.0f;
		Armor = 80.0f;
		Energy = 120.0f;
		CockpitModifiers.RadarBoost = 5.0f; // No radar boost for large cockpits
		CockpitModifiers.VisionRange = 20.0f; // Larger vision range
		break;

	default:
		// Default to medium if no size is specified
		Health = 100.0f;
		Speed = 100.0f;
		Armor = 50.0f;
		Energy = 100.0f;
		break;
	}
}

// Set or upgrade a specific cockpit perk
void UCockpitSystem::SetCockpitPerk(FString PerkName, bool bIsActive)
{
	if (bIsActive)
	{
		// Add the perk to active perks list
		ActivePerks.Add(PerkName);
	}
	else
	{
		// Remove the perk if it was deactivated
		ActivePerks.Remove(PerkName);
	}
}

// Get the current health of the cockpit
float UCockpitSystem::GetCockpitHealth() const
{
	return Health;
}

// Get the current speed of the cockpit
float UCockpitSystem::GetCockpitSpeed() const
{
	return Speed;
}

// Get the current armor of the cockpit
float UCockpitSystem::GetCockpitArmor() const
{
	return Armor;
}

// Get the current energy level of the cockpit
float UCockpitSystem::GetCockpitEnergy() const
{
	return Energy;
}

// Activate an upgrade perk for the cockpit
void UCockpitSystem::ActivateUpgradePerk(FString PerkName)
{
	if (!AvailablePerks.Contains(PerkName))
	{
		// You can add logic here to check if the perk is valid or available
		AvailablePerks.Add(PerkName);
	}
}

// Deactivate an upgrade perk if needed
void UCockpitSystem::DeactivateUpgradePerk(FString PerkName)
{
	// Remove the perk from available perks
	AvailablePerks.Remove(PerkName);
}