// Aegis Protocol - AssaultClass.cpp
// Implements Assault Mech class with armor-piercing perks and combat-focused abilities.

#include "AssaultClass.h"
#include "TimerManager.h"

AAssaultClass::AAssaultClass()
{
    // Default Assault Mech stats
    MechHealth = 1250.0f;  // Slightly more durable than other classes
    MovementSpeed = 450.0f;  // Balanced speed
    FirepowerMultiplier = 1.15f;  // 15% bonus to mid-range weapons

    bArmorPiercingActive = false;
    ArmorPiercingDuration = 10.0f; // Lasts 10 seconds
}

void AAssaultClass::BeginPlay()
{
    Super::BeginPlay();
    ApplyAssaultPerks();
}

void AAssaultClass::ApplyAssaultPerks()
{
    // Assault Class Perks: Bonus Damage on mid-range weapons
    if (EquippedWeapon)
    {
        if (EquippedWeapon->WeaponType == EWeaponType::AssaultRifle || EquippedWeapon->WeaponType == EWeaponType::Shotgun)
        {
            EquippedWeapon->Damage *= FirepowerMultiplier;
            EquippedWeapon->ReloadSpeed *= 0.90f;  // 10% faster reload
        }
    }
}

void AAssaultClass::Attack()
{
    if (EquippedWeapon)
    {
        if (bArmorPiercingActive)
        {
            EquippedWeapon->Damage *= 1.25f; // 25% more damage while Armor-Piercing is active
        }

        EquippedWeapon->Fire();
    }
}

void AAssaultClass::ActivateArmorPiercingMode()
{
    if (!bArmorPiercingActive)
    {
        bArmorPiercingActive = true;

        // Log activation
        UE_LOG(LogTemp, Log, TEXT("Armor Piercing Mode Activated!"));

        // Set a timer to reset the ability after duration
        GetWorldTimerManager().SetTimer(ArmorPiercingCooldownHandle, this, &AAssaultClass::ResetArmorPiercing, ArmorPiercingDuration, false);
    }
}

void AAssaultClass::ResetArmorPiercing()
{
    bArmorPiercingActive = false;
    UE_LOG(LogTemp, Log, TEXT("Armor Piercing Mode Deactivated"));
}