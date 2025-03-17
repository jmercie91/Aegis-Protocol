// Aegis Protocol - WeaponSystem.cpp
// Implements weapon slotting, ammo, ballistics, and firing logic.

#include "WeaponSystem.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AWeaponSystem::AWeaponSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    TotalWeight = 0.0f;
}

void AWeaponSystem::BeginPlay()
{
    Super::BeginPlay();
}

void AWeaponSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeaponSystem::FireWeapon()
{
    for (const auto& Weapon : EquippedWeapons)
    {
        FWeaponStats WeaponStats = Weapon.Value;

        if (WeaponStats.AmmoType == EAmmoType::Explosive)
        {
            UE_LOG(LogTemp, Log, TEXT("Firing Explosive Round! Damage: %.2f"), WeaponStats.Damage);
        }
        else if (WeaponStats.AmmoType == EAmmoType::ArmorPiercing)
        {
            UE_LOG(LogTemp, Log, TEXT("Firing Armor-Piercing Round! Damage: %.2f"), WeaponStats.Damage);
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Firing Standard Round! Damage: %.2f"), WeaponStats.Damage);
        }

        if (WeaponStats.bHasHeatMechanic)
        {
            WeaponStats.HeatBuildUp += 5.0f;
            UE_LOG(LogTemp, Log, TEXT("Weapon Heat Increased: %.2f"), WeaponStats.HeatBuildUp);
        }

        if (WeaponStats.HeatBuildUp >= 100.0f)
        {
            UE_LOG(LogTemp, Warning, TEXT("Weapon Overheated! Wait for cooldown."));
        }
    }
}

void AWeaponSystem::ReloadWeapon()
{
    UE_LOG(LogTemp, Log, TEXT("Reloading Weapon!"));
}

void AWeaponSystem::AttachWeapon(EWeaponSlot Slot, FWeaponStats Weapon)
{
    if (EquippedWeapons.Contains(Slot))
    {
        UE_LOG(LogTemp, Warning, TEXT("Replacing weapon in slot %d"), (uint8)Slot);
    }

    EquippedWeapons.Add(Slot, Weapon);
    TotalWeight += Weapon.Weight;

    UE_LOG(LogTemp, Log, TEXT("Weapon Attached in Slot: %d | Total Weight: %.2f"), (uint8)Slot, TotalWeight);
}

float AWeaponSystem::GetWeaponWeight()
{
    return TotalWeight;
}