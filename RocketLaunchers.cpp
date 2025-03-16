#include "RocketLaunchers.h"
#include "Engine/World.h"
#include "ProjectileRocket.h"
#include "Kismet/GameplayStatics.h"

ARocketLaunchers::ARocketLaunchers()
{
    PrimaryActorTick.bCanEverTick = true;
    RocketLauncherVariant = ERocketLauncherType::BarrageRL6;
    SetupWeaponStats();
}

void ARocketLaunchers::SetupWeaponStats()
{
    switch (RocketLauncherVariant)
    {
    case ERocketLauncherType::BarrageRL6:
        AmmoCount = 6;
        MaxAmmo = 6;
        ReloadTime = 2.5f;
        ExplosionRadius = 250.0f;
        break;
    case ERocketLauncherType::TyphoonRL9:
        AmmoCount = 5;
        MaxAmmo = 5;
        ReloadTime = 3.0f;
        ExplosionRadius = 275.0f;
        break;
    case ERocketLauncherType::DoombringerRL15:
        AmmoCount = 3;
        MaxAmmo = 3;
        ReloadTime = 3.5f;
        ExplosionRadius = 300.0f;
        break;
    case ERocketLauncherType::OblivionRL20:
        AmmoCount = 2;
        MaxAmmo = 2;
        ReloadTime = 4.0f;
        ExplosionRadius = 350.0f;
        break;
    case ERocketLauncherType::JudgmentRL25:
        AmmoCount = 1;
        MaxAmmo = 1;
        ReloadTime = 4.5f;
        ExplosionRadius = 400.0f;
        break;
    }
}

void ARocketLaunchers::FireWeapon()
{
    if (AmmoCount > 0)
    {
        AmmoCount--;

        FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator MuzzleRotation = GetActorRotation();

        AProjectileRocket* SpawnedRocket = GetWorld()->SpawnActor<AProjectileRocket>(AProjectileRocket::StaticClass(), MuzzleLocation, MuzzleRotation);
        UE_LOG(LogTemp, Log, TEXT("Rocket Fired! Ammo remaining: %d"), AmmoCount);
    }
}

void ARocketLaunchers::ReloadWeapon()
{
    AmmoCount = MaxAmmo;
    UE_LOG(LogTemp, Log, TEXT("Reloading Rocket Launcher. Ammo refilled to: %d"), MaxAmmo);
}