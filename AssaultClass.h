// Aegis Protocol - AssaultClass.h
// Defines the Assault Mech class with mid-range combat capabilities and armor-piercing perks.

#pragma once

#include "CoreMinimal.h"
#include "MechCharacter.h"
#include "AssaultClass.generated.h"

UCLASS()
class AEGISPROTOCOL_API AAssaultClass : public AMechCharacter
{
    GENERATED_BODY()

public:
    // Constructor
    AAssaultClass();

    // Override attack method for unique Assault playstyle
    virtual void Attack() override;

    // Special ability: Armor-Piercing Mode
    void ActivateArmorPiercingMode();

    // Handles perk-based adjustments
    void ApplyAssaultPerks();

protected:
    virtual void BeginPlay() override;

private:
    // Armor-Piercing Ability
    UPROPERTY(EditAnywhere, Category = "Assault Perks")
    bool bArmorPiercingActive;

    // Duration for the ability
    UPROPERTY(EditAnywhere, Category = "Assault Perks")
    float ArmorPiercingDuration;

    // Timer handle for ability cooldown
    FTimerHandle ArmorPiercingCooldownHandle;

    // Handles cooldown expiration
    void ResetArmorPiercing();
};

