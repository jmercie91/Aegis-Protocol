// Aegis Protocol - WeaponSystem.h
// Manages core weapon mechanics, firing, reloading, and ammo system

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponSystem.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Sniper UMETA(DisplayName = "Sniper"),
    AssaultRifle UMETA(DisplayName = "Assault Rifle"),
    Shotgun UMETA(DisplayName = "Shotgun"),
    MachineGun UMETA(DisplayName = "Machine Gun"),
    RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
    GrenadeLauncher UMETA(DisplayName = "Grenade Launcher"),
    LockOnWeapon UMETA(DisplayName = "Lock-On Weapon"),
    MeleeWeapon UMETA(DisplayName = "Melee"),
    EMPWeapon UMETA(DisplayName = "EMP")
};

UCLASS()
class AEGISPROTOCOL_API AWeaponSystem : public AActor
{
    GENERATED_BODY()

public:
    AWeaponSystem();

    virtual void Tick(float DeltaTime) override;
    void FireWeapon();
    void ReloadWeapon();
    bool CanFire() const;
    void ApplyWeaponEffects(AActor* HitTarget);
    void SwitchWeapon(EWeaponType NewWeaponType);
    EWeaponType GetCurrentWeaponType() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    EWeaponType CurrentWeaponType;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    int32 AmmoCount;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    int32 MaxAmmo;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    float FireRate;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    float ReloadTime;

    UPROPERTY(EditAnywhere, Category = "Weapon Properties")
    bool bIsReloading;

    void StartReload();
    void FinishReload();
};