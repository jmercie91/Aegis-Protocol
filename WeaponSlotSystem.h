// Aegis Protocol - WeaponSlotSystem.h
// Manages weapon slots (Left, Right, Head), allowing up to 3 of the same weapon type.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponSystem.h"
#include "WeaponSlotSystem.generated.h"

UCLASS()
class AEGISPROTOCOL_API AWeaponSlotSystem : public AActor
{
    GENERATED_BODY()

public:
    AWeaponSlotSystem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Equip a weapon to a slot (Left, Right, Head)
    UFUNCTION(BlueprintCallable, Category = "WeaponSlot")
    bool EquipWeapon(EWeaponSlot Slot, FWeaponStats Weapon);

    // Remove a weapon from a slot
    UFUNCTION(BlueprintCallable, Category = "WeaponSlot")
    void RemoveWeapon(EWeaponSlot Slot);

    // Get currently equipped weapons
    UFUNCTION(BlueprintCallable, Category = "WeaponSlot")
    FWeaponStats GetEquippedWeapon(EWeaponSlot Slot) const;

    // Rotate to next weapon configuration
    UFUNCTION(BlueprintCallable, Category = "WeaponSlot")
    void RotateWeaponConfig();

private:
    // Stores the equipped weapons for each slot
    TMap<EWeaponSlot, FWeaponStats> EquippedWeapons;

    // Weapon loadout configurations (allows players to save 3 different loadouts)
    TArray<TMap<EWeaponSlot, FWeaponStats>> WeaponConfigurations;

    int32 CurrentConfigIndex; // Tracks the current active loadout

    void ApplyWeaponConfiguration();
};