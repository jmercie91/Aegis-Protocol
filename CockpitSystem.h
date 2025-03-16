#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CockpitSystem.generated.h"

// Enum for different cockpit sizes
UENUM(BlueprintType)
enum class ECockpitSize : uint8
{
	Small     UMETA(DisplayName = "Small"),
	Medium    UMETA(DisplayName = "Medium"),
	Large     UMETA(DisplayName = "Large"),
	XLarge    UMETA(DisplayName = "XLarge"),
	Stealth   UMETA(DisplayName = "Stealth"),
	Support   UMETA(DisplayName = "Support"),
	Artillery UMETA(DisplayName = "Artillery"),
	Assault   UMETA(DisplayName = "Assault"),
	Scout     UMETA(DisplayName = "Scout"),
	Heavy     UMETA(DisplayName = "Heavy"),
	Demolition UMETA(DisplayName = "Demolition"),
	Espionage UMETA(DisplayName = "Espionage")
};

// Struct to hold cockpit-specific modifiers (for example: radar boost, explosive damage boost, etc.)
USTRUCT(BlueprintType)
struct FCockpitModifiers
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifiers")
	float RadarBoost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifiers")
	float VisionRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifiers")
	float StealthLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifiers")
	bool bIsArtilleryEnabled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifiers")
	float SpeedBoost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifiers")
	float HealthBoost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifiers")
	float ExplosiveDamageBoost;  // Added for Demolition

	FCockpitModifiers()
		: RadarBoost(0.0f), VisionRange(0.0f), StealthLevel(0.0f), bIsArtilleryEnabled(false), SpeedBoost(0.0f), HealthBoost(0.0f), ExplosiveDamageBoost(0.0f) {
	}
};

UCLASS(Blueprintable)
class AEGISPROTOCOL_API UCockpitSystem : public UObject
{
	GENERATED_BODY()

public:
	// Constructor to initialize default values
	UCockpitSystem();

	// Called when the cockpit is initialized or reset
	void InitializeCockpit(int32 PlayerID, int32 TeamID, ECockpitSize CockpitSize);

	// Update the cockpit with new stats or upgrades
	void UpdateCockpitStats();

	// Set or upgrade a specific cockpit perk
	UFUNCTION(BlueprintCallable, Category = "Cockpit")
	void SetCockpitPerk(FString PerkName, bool bIsActive);

	// Get the current health of the cockpit
	UFUNCTION(BlueprintCallable, Category = "Cockpit")
	float GetCockpitHealth() const;

	// Get the current speed of the cockpit
	UFUNCTION(BlueprintCallable, Category = "Cockpit")
	float GetCockpitSpeed() const;

	// Get the current armor of the cockpit
	UFUNCTION(BlueprintCallable, Category = "Cockpit")
	float GetCockpitArmor() const;

	// Get the current energy level of the cockpit
	UFUNCTION(BlueprintCallable, Category = "Cockpit")
	float GetCockpitEnergy() const;

	// Activate an upgrade slot perk
	UFUNCTION(BlueprintCallable, Category = "Cockpit")
	void ActivateUpgradePerk(FString PerkName);

	// Deactivate a perk when needed (for example when changing parts or losing a perk)
	UFUNCTION(BlueprintCallable, Category = "Cockpit")
	void DeactivateUpgradePerk(FString PerkName);

protected:
	// The health of the cockpit
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cockpit Stats")
	float Health;

	// The speed of the cockpit
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cockpit Stats")
	float Speed;

	// The armor level of the cockpit
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cockpit Stats")
	float Armor;

	// The energy available to the cockpit for special functions
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cockpit Stats")
	float Energy;

	// List of active perks for this cockpit
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cockpit Perks")
	TArray<FString> ActivePerks;

	// List of available upgrade perks
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cockpit Upgrade Perks")
	TArray<FString> AvailablePerks;

	// Cockpit size (Small, Medium, Large, Stealth, Support, Artillery, etc.)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cockpit Stats")
	ECockpitSize CockpitSize;

	// Cockpit modifiers (e.g., radar boost, vision range, stealth capabilities, explosive damage boost)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cockpit Modifiers")
	FCockpitModifiers CockpitModifiers;

private:
	// Player ID associated with this cockpit
	int32 PlayerID;

	// Team ID for the team owning this cockpit
	int32 TeamID;
};