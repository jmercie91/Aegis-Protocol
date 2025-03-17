// Aegis Protocol - DemolitionClass.cpp
// Implements Demolition Mech class with explosive-focused combat and siege mode ability.

#include "DemolitionClass.h"
#include "TimerManager.h"

ADemolitionClass::ADemolitionClass()
{
    // Default Demolition Mech stats
    MechHealth = 1500.0f;  // Heaviest armor class
    MovementSpeed = 350.0f;  // Slowest speed due to armor
    FirepowerMultiplier = 1.20f;  // 20% extra explosive damage

    bSiegeModeActive = false;
    SiegeModeDuration = 12.0f; // Siege Mode lasts 12 seconds
}

void ADemolitionClass::BeginPlay()
{
    Super::BeginPlay();
    ApplyDemolitionPerks();
}

void ADemolitionClass::ApplyDemolitionPerks()
{
    // Demolition Class Perks: Increased explosive weapon damage
    if (EquippedWeapon)
    {
        if (EquippedWeapon->WeaponType == EWeaponType::RocketLauncher || EquippedWeapon->WeaponType == EWeaponType::GrenadeLauncher)
        {
            EquippedWeapon->Damage *= FirepowerMultiplier;
            EquippedWeapon->SplashRadius *= 1.15f;  // 15% bigger explosion radius
        }
    }
}

void ADemolitionClass::Attack()
{
    if (EquippedWeapon)
    {
        if (bSiegeModeActive)
        {
            EquippedWeapon->Damage *= 1.35f; // 35% more damage while Siege Mode is active
            EquippedWeapon->SplashRadius *= 1.20f; // 20% larger explosion radius
        }

        EquippedWeapon->Fire();
    }
}

void ADemolitionClass::ActivateSiegeMode()
{
    if (!bSiegeModeActive)
    {
        bSiegeModeActive = true;

        // Log activation
        UE_LOG(LogTemp, Log, TEXT("Siege Mode Activated!"));

        // Set a timer to reset the ability after duration
        GetWorldTimerManager().SetTimer(SiegeModeCooldownHandle, this, &ADemolitionClass::ResetSiegeMode, SiegeModeDuration, false);
    }
}

void ADemolitionClass::ResetSiegeMode()
{
    bSiegeModeActive = false;
    UE_LOG(LogTemp, Log, TEXT("Siege Mode Deactivated"));
}