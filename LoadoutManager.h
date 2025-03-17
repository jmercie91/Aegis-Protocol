// Aegis Protocol - LoadoutManager.h
// Manages mech customization, weapon selection, armor application, and loadout persistence.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponSlotSystem.h"
#include "ArmorSystem.h"
#include "AmmoTypes.h"
#include "LoadoutManager.generated.h"

USTRUCT(BlueprintType)
struct FMechLoadout
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Loadout")
    FString LoadoutName;

    UPROPERTY(BlueprintReadWrite, Category = "Loadout")
    TMap<EWeaponSlot, FString> Weapons; // Map of weapons per slot

    UPROPERTY(BlueprintReadWrite, Category = "Loadout")
    TMap<EWeaponSlot, EAmmoType> AmmoTypes; // Ammo selection for each weapon slot

    UPROPERTY(BlueprintReadWrite, Category = "Loadout")
    EArmorType ArmorType; // Armor selection

    UPROPERTY(BlueprintReadWrite, Category = "Loadout")
    float Health;

    UPROPERTY(BlueprintReadWrite, Category = "Loadout")
    float Speed;

    UPROPERTY(BlueprintReadWrite, Category = "Loadout")
    float ArmorValue;

    UPROPERTY(BlueprintReadWrite, Category = "Loadout")
    float Energy;
};

UCLASS()
class AEGISPROTOCOL_API ALoadoutManager : public AActor
{
    GENERATED_BODY()

public:
    ALoadoutManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Loadout")
    FMechLoadout LoadLoadout();

    UFUNCTION(BlueprintCallable, Category = "Loadout")
    void ApplyLoadoutToMech(const FMechLoadout& Loadout);

    UFUNCTION(BlueprintCallable, Category = "Loadout")
    void SaveLoadout(const FMechLoadout& Loadout);

private:
    void EquipWeapon(EWeaponSlot Slot, const FString& WeaponName, EAmmoType AmmoType);
    void ApplyArmor(EArmorType ArmorType);
    void UpdateMechStats(const FMechLoadout& Loadout);
};