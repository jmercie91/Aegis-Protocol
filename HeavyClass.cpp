// Aegis Protocol - HeavyClass.cpp
// Implements the Heavy Mech class with high armor and offensive capabilities.

#include "HeavyClass.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "MechCharacter.h"

AHeavyClass::AHeavyClass()
{
    // Default Heavy Mech stats
    MechHealth = 2000.0f;  // High durability
    MovementSpeed = 350.0f;  // Slow movement speed
    FirepowerMultiplier = 1.25f;  // Increased firepower for heavy weapons

    bDefensiveShieldActive = false;
    DefensiveShieldDuration = 8.0f;  // Lasts for 8 seconds
    DefensiveShieldCooldown = 20.0f;  // Cooldown before reuse
    DamageReductionFactor = 0.5f;  // Reduces incoming damage by 50%

    bOverdriveActive = false;
    OverdriveFireRateBoost = 1.5f;  // Increases fire rate by 50%
    OverdriveSpeedPenalty = 0.6f;  // Reduces movement speed to 60%
    OverdriveDuration = 10.0f;  // Lasts for 10 seconds
    OverdriveCooldown = 25.0f;  // Cooldown before reuse
}

void AHeavyClass::BeginPlay()
{
    Super::BeginPlay();
}

void AHeavyClass::Attack()
{
    if (EquippedWeapon)
    {
        EquippedWeapon->Fire();
    }
}

void AHeavyClass::ActivateDefensiveShield()
{
    if (!bDefensiveShieldActive)
    {
        bDefensiveShieldActive = true;

        // Log activation
        UE_LOG(LogTemp, Log, TEXT("Defensive Shield Activated! Incoming damage reduced."));

        // Reduce incoming damage effect
        DamageMultiplier = DamageReductionFactor;

        // Set a timer to reset the ability after duration
        GetWorldTimerManager().SetTimer(DefensiveShieldCooldownHandle, this, &AHeavyClass::ResetDefensiveShield, DefensiveShieldDuration, false);
    }
}

void AHeavyClass::ResetDefensiveShield()
{
    bDefensiveShieldActive = false;
    DamageMultiplier = 1.0f;  // Reset damage back to normal
    UE_LOG(LogTemp, Log, TEXT("Defensive Shield Deactivated."));
}

void AHeavyClass::ActivateOverdriveMode()
{
    if (!bOverdriveActive)
    {
        bOverdriveActive = true;

        // Log activation
        UE_LOG(LogTemp, Log, TEXT("Overdrive Mode Activated! Fire rate increased, movement reduced."));

        // Apply overdrive effects
        FirepowerMultiplier *= OverdriveFireRateBoost;
        MovementSpeed *= OverdriveSpeedPenalty;

        // Set a timer to reset Overdrive Mode
        GetWorldTimerManager().SetTimer(OverdriveCooldownHandle, this, &AHeavyClass::ResetOverdriveMode, OverdriveDuration, false);
    }
}

void AHeavyClass::ResetOverdriveMode()
{
    bOverdriveActive = false;
    FirepowerMultiplier /= OverdriveFireRateBoost;  // Reset fire rate
    MovementSpeed /= OverdriveSpeedPenalty;  // Reset movement speed
    UE_LOG(LogTemp, Log, TEXT("Overdrive Mode Deactivated."));
}