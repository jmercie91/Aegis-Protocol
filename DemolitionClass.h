// Aegis Protocol - DemolitionClass.h
// Defines the Demolition Mech class with explosive-focused abilities.

#pragma once

#include "CoreMinimal.h"
#include "MechCharacter.h"
#include "DemolitionClass.generated.h"

UCLASS()
class AEGISPROTOCOL_API ADemolitionClass : public AMechCharacter
{
    GENERATED_BODY()

public:
    // Constructor
    ADemolitionClass();

    // Overrides attack method for explosive mechanics
    virtual void Attack() override;

    // Special ability: Siege Mode (enhances explosive damage)
    void ActivateSiegeMode();

    // Handles perk-based adjustments
    void ApplyDemolitionPerks();

protected:
    virtual void BeginPlay() override;

private:
    // Siege Mode Ability
    UPROPERTY(EditAnywhere, Category = "Demolition Perks")
    bool bSiegeModeActive;

    // Duration for Siege Mode
    UPROPERTY(EditAnywhere, Category = "Demolition Perks")
    float SiegeModeDuration;

    // Timer handle for Siege Mode cooldown
    FTimerHandle SiegeModeCooldownHandle;

    // Resets Siege Mode effects
    void ResetSiegeMode();
};

