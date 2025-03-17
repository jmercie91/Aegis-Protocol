// Aegis Protocol - WeaponSystem.h
// Manages all weapons, firing logic, weight calculations, and slot system.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoTypes.h"
#include "WeaponSlotSystem.h" // Integrating the slot system
#include "WeaponSystem.generated.h"

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
    Left UMETA(DisplayName = "Left Side"),
    Right UMETA(DisplayName = "Right Side"),
    Head UMETA(DisplayName = "Head Slot")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    SniperRifle UMETA(DisplayName = "Sniper Rifle"),
    AssaultRifle UMETA(DisplayName = "Assault Rifle"),
    Shotgun UMETA(DisplayName = "Shotgun"),
    MachineGun UMETA(DisplayName = "Machine Gun"),
    RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
    GrenadeLauncher UMETA(DisplayName = "Grenade Launcher"),
    LockOnMissile UMETA(DisplayName = "Lock-On Missile"),
    MeleeWeapon UMETA(DisplayName = "Melee Weapon"),
    EMPWeapon UMETA(DisplayName = "EMP Weapon")
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Range;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    EAmmoType AmmoType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    bool bHasHeatMechanic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float HeatBuildUp;
};

UCLASS()
class AEGISPROTOCOL_API AWeaponSystem : public AActor
{
    GENERATED_BODY()

public:
    AWeaponSystem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void FireWeapon();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void ReloadWeapon();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void AttachWeapon(EWeaponSlot Slot, FWeaponStats Weapon);

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    float GetWeaponWeight();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void SwitchWeapon(EWeaponType NewWeaponType);

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    EWeaponType GetCurrentWeaponType() const;

private:
    TMap<EWeaponSlot, FWeaponStats> EquippedWeapons;
    UPROPERTY(EditAnywhere, Category = "Weapon Config")
    float TotalWeight;

    UPROPERTY()
    AWeaponSlotSystem* WeaponSlotSystem; // Link to weapon slot system

    void ApplyWeaponEffects(AActor* HitTarget);
    bool CanFire() const;
    void StartReload();
    void FinishReload();
};