// Aegis Protocol - EspionageClass.h
// Defines the Espionage Mech class with radar disruption and intelligence-gathering capabilities.

#pragma once

#include "CoreMinimal.h"
#include "MechCharacter.h"
#include "EspionageClass.generated.h"

UCLASS()
class AEGISPROTOCOL_API AEspionageClass : public AMechCharacter
{
    GENERATED_BODY()

public:
    // Constructor
    AEspionageClass();

    // Overrides standard attack for intel-based gameplay
    virtual void Attack() override;

    // Special ability: Radar Jammer (Disables enemy radar within range)
    void ActivateRadarJammer();

    // Special ability: Recon Ping (Reveals enemy positions in a radius)
    void ActivateReconPing();

    // Applies Espionage Class Perks
    void ApplyEspionagePerks();

protected:
    virtual void BeginPlay() override;

private:
    // Radar Jammer Ability
    UPROPERTY(EditAnywhere, Category = "Espionage Perks")
    bool bRadarJammerActive;

    // Duration for Radar Jammer
    UPROPERTY(EditAnywhere, Category = "Espionage Perks")
    float RadarJammerDuration;

    // Cooldown for Radar Jammer
    UPROPERTY(EditAnywhere, Category = "Espionage Perks")
    float RadarJammerCooldown;

    // Timer handle for Radar Jammer reset
    FTimerHandle RadarJammerCooldownHandle;

    // Recon Ping Ability
    UPROPERTY(EditAnywhere, Category = "Espionage Perks")
    float ReconPingRadius;

    // Cooldown for Recon Ping
    UPROPERTY(EditAnywhere, Category = "Espionage Perks")
    float ReconPingCooldown;

    // Timer handle for Recon Ping reset
    FTimerHandle ReconPingCooldownHandle;

    // Resets Radar Jammer effects
    void ResetRadarJammer();

    // Resets Recon Ping ability cooldown
    void ResetReconPing();
};