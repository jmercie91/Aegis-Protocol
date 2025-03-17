// Aegis Protocol - PerkSystem.h
// Manages mech class perks and nation-specific abilities.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerkSystem.generated.h"

// Enum for Standard Perks
UENUM(BlueprintType)
enum class EStandardPerk : uint8
{
    EmergencyEscape UMETA(DisplayName = "Emergency Escape"),
    EnhancedRadar UMETA(DisplayName = "Enhanced Radar"),
    ReinforcedArmor UMETA(DisplayName = "Reinforced Armor"),
    AmmoSpecialist UMETA(DisplayName = "Ammo Specialist"),
    TargetingAssist UMETA(DisplayName = "Targeting Assist"),
    SpeedTuning UMETA(DisplayName = "Speed Tuning")
};

// Enum for Nation-Specific Perks
UENUM(BlueprintType)
enum class ENationPerk : uint8
{
    UnitedFront UMETA(DisplayName = "15% increased visibility for specific guns"),
    SandVeil UMETA(DisplayName = "Reduces sandstorm penalties by 20%"),
    IronUnion UMETA(DisplayName = "20% reduced movement penalties in snow"),
    ShadowLegion UMETA(DisplayName = "Adaptive camouflage in jungle terrain")
};

UCLASS()
class AEGISPROTOCOL_API APerkSystem : public AActor
{
    GENERATED_BODY()

public:
    APerkSystem();

    // Set or swap the chosen perk for the player
    void SetStandardPerk(AActor* Mech, EStandardPerk ChosenStandardPerk);
    void SetNationPerk(AActor* Mech, ENationPerk ChosenNationPerk);

    // Remove selected perk (for swapping in the garage)
    void RemoveSelectedPerk(AActor* Mech);

    // Get the currently active perk
    EStandardPerk GetSelectedStandardPerk();
    ENationPerk GetSelectedNationPerk();

protected:
    virtual void BeginPlay() override;

private:
    // Active perk (either standard or nation-specific, but not both)
    bool bHasSelectedStandardPerk;
    bool bHasSelectedNationPerk;
    EStandardPerk ActiveStandardPerk;
    ENationPerk ActiveNationPerk;
};

