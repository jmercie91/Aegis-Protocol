// Aegis Protocol - WeaponSystem.cpp
// Implements core weapon mechanics, firing, reloading, and ammo system

#include "WeaponSystem.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AWeaponSystem::AWeaponSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentWeaponType = EWeaponType::AssaultRifle;
    MaxAmmo = 30;
    AmmoCount = MaxAmmo;
    FireRate = 0.1f;
    ReloadTime = 2.5f;
    bIsReloading = false;
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
    if (CanFire())
    {
        AmmoCount--;

        FVector MuzzleLocation = GetActorLocation();
        FRotator MuzzleRotation = GetActorRotation();
        FHitResult HitResult;

        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);

        FVector Start = MuzzleLocation;
        FVector End = Start + (MuzzleRotation.Vector() * 10000.0f); // Simulated bullet distance

        if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
        {
            ApplyWeaponEffects(HitResult.GetActor());
        }

        UE_LOG(LogTemp, Log, TEXT("Weapon fired: %s | Ammo left: %d"), *UEnum::GetValueAsString(CurrentWeaponType), AmmoCount);
    }
    else
    {
        if (AmmoCount <= 0)
        {
            StartReload();
        }
    }
}

void AWeaponSystem::ApplyWeaponEffects(AActor* HitTarget)
{
    if (HitTarget)
    {
        UE_LOG(LogTemp, Log, TEXT("Hit Target: %s"), *HitTarget->GetName());

        switch (CurrentWeaponType)
        {
        case EWeaponType::Sniper:
            // High damage, long-range shot
            break;
        case EWeaponType::AssaultRifle:
            // Moderate damage, rapid fire
            break;
        case EWeaponType::Shotgun:
            // Close-range spread damage
            break;
        case EWeaponType::MachineGun:
            // Suppression fire, low accuracy
            break;
        case EWeaponType::RocketLauncher:
            // Explosion at impact
            break;
        case EWeaponType::GrenadeLauncher:
            // Bouncing projectile, AoE explosion
            break;
        case EWeaponType::LockOnWeapon:
            // Homing missile tracking
            break;
        case EWeaponType::MeleeWeapon:
            // Heavy melee attack
            break;
        case EWeaponType::EMPWeapon:
            // Disables enemy radar
            break;
        }
    }
}

bool AWeaponSystem::CanFire() const
{
    return AmmoCount > 0 && !bIsReloading;
}

void AWeaponSystem::StartReload()
{
    if (!bIsReloading)
    {
        bIsReloading = true;
        UE_LOG(LogTemp, Log, TEXT("Reloading..."));
        GetWorldTimerManager().SetTimer(CaptureTimerHandle, this, &AWeaponSystem::FinishReload, ReloadTime, false);
    }
}

void AWeaponSystem::FinishReload()
{
    AmmoCount = MaxAmmo;
    bIsReloading = false;
    UE_LOG(LogTemp, Log, TEXT("Reload Complete"));
}

void AWeaponSystem::SwitchWeapon(EWeaponType NewWeaponType)
{
    CurrentWeaponType = NewWeaponType;

    switch (NewWeaponType)
    {
    case EWeaponType::Sniper:
        MaxAmmo = 5;
        FireRate = 1.5f;
        break;
    case EWeaponType::AssaultRifle:
        MaxAmmo = 30;
        FireRate = 0.1f;
        break;
    case EWeaponType::Shotgun:
        MaxAmmo = 6;
        FireRate = 0.8f;
        break;
    case EWeaponType::MachineGun:
        MaxAmmo = 100;
        FireRate = 0.05f;
        break;
    case EWeaponType::RocketLauncher:
        MaxAmmo = 4;
        FireRate = 2.0f;
        break;
    case EWeaponType::GrenadeLauncher:
        MaxAmmo = 6;
        FireRate = 1.2f;
        break;
    case EWeaponType::LockOnWeapon:
        MaxAmmo = 10;
        FireRate = 1.0f;
        break;
    case EWeaponType::MeleeWeapon:
        MaxAmmo = -1;
        FireRate = 0.7f;
        break;
    case EWeaponType::EMPWeapon:
        MaxAmmo = 2;
        FireRate = 2.5f;
        break;
    }

    AmmoCount = MaxAmmo;
}

EWeaponType AWeaponSystem::GetCurrentWeaponType() const
{
    return CurrentWeaponType;
}