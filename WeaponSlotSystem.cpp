// Aegis Protocol - WeaponSlotSystem.cpp
// Implements logic for weapon slot management and configuration rotation.

#include "WeaponSlotSystem.h"
#include "Kismet/GameplayStatics.h"

AWeaponSlotSystem::AWeaponSlotSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentConfigIndex = 0;
}

void AWeaponSlotSystem::BeginPlay()
{
    Super::BeginPlay();
}

void AWeaponSlotSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AWeaponSlotSystem::EquipWeapon(EWeaponSlot Slot, FWeaponStats Weapon)
{
    if (EquippedWeapons.Contains(Slot))
    {
        UE_LOG(LogTemp, Warning, TEXT("Slot %s already has a weapon! Replacing with %s"), *UEnum::GetValueAsString(Slot), *UEnum::GetValueAsString(Weapon.WeaponType));
    }

    EquippedWeapons.Add(Slot, Weapon);
    UE_LOG(LogTemp, Log, TEXT("Equipped %s on %s"), *UEnum::GetValueAsString(Weapon.WeaponType), *UEnum::GetValueAsString(Slot));

    return true;
}

void AWeaponSlotSystem::RemoveWeapon(EWeaponSlot Slot)
{
    if (EquippedWeapons.Contains(Slot))
    {
        UE_LOG(LogTemp, Log, TEXT("Removed weapon from slot: %s"), *UEnum::GetValueAsString(Slot));
        EquippedWeapons.Remove(Slot);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No weapon found in slot: %s"), *UEnum::GetValueAsString(Slot));
    }
}

FWeaponStats AWeaponSlotSystem::GetEquippedWeapon(EWeaponSlot Slot) const
{
    if (EquippedWeapons.Contains(Slot))
    {
        return EquippedWeapons[Slot];
    }

    return FWeaponStats(); // Return an empty struct if slot is empty
}

void AWeaponSlotSystem::RotateWeaponConfig()
{
    if (WeaponConfigurations.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No weapon configurations available!"));
        return;
    }

    // Cycle to the next loadout
    CurrentConfigIndex = (CurrentConfigIndex + 1) % WeaponConfigurations.Num();
    ApplyWeaponConfiguration();

    UE_LOG(LogTemp, Log, TEXT("Switched to weapon configuration %d"), CurrentConfigIndex);
}

void AWeaponSlotSystem::ApplyWeaponConfiguration()
{
    if (WeaponConfigurations.Num() > 0)
    {
        EquippedWeapons = WeaponConfigurations[CurrentConfigIndex];
        UE_LOG(LogTemp, Log, TEXT("Applied new weapon configuration"));
    }
}