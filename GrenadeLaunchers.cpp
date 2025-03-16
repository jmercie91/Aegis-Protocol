#include "GrenadeLaunchers.h"
#include "Engine/World.h"
#include "ProjectileGrenade.h"
#include "Kismet/GameplayStatics.h"

AGrenadeLaunchers::AGrenadeLaunchers()
{
    PrimaryActorTick.bCanEverTick = true;
    GrenadeLauncherVariant = EGrenadeLauncherType::RattlesnakeGL3;
    SetupWeaponStats();
}

void AGrenadeLaunchers::SetupWeaponStats()
{
    switch (GrenadeLauncherVariant)
    {
    case EGrenadeLauncherType::RattlesnakeGL3:
        AmmoCount = 5;
        MaxAmmo = 5;
        ExplosionRadius = 250.0f;
        BounceCount = 2;
        break;

    case EGrenadeLauncherType::AnacondaGL7:
        AmmoCount = 4;
        MaxAmmo = 4;
        ExplosionRadius = 275.0f;
        BounceCount = 3;
        break;

    case EGrenadeLauncherType::PythonGL10:
        AmmoCount = 3;
        MaxAmmo = 3;
        ExplosionRadius = 300.0f;
        BounceCount = 4;
        break;

    case EGrenadeLauncherType::BasiliskGL16:
        AmmoCount = 2;
        MaxAmmo = 2;
        ExplosionRadius = 350.0f;
        BounceCount = 5;
        break;

    case EGrenadeLauncherType::VenomGL20:
        AmmoCount = 1;
        MaxAmmo = 1;
        ExplosionRadius = 400.0f;
        BounceCount = 6;
        break;
    }
}

void AGrenadeLaunchers::FireWeapon()
{
    if (AmmoCount > 0)
    {
        AmmoCount--;

        FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator MuzzleRotation = GetActorRotation();

        AProjectileGrenade* SpawnedGrenade = GetWorld()->SpawnActor<AProjectileGrenade>(AProjectileGrenade::StaticClass(), MuzzleLocation, MuzzleRotation);
        if (SpawnedGrenade)
        {
            SpawnedGrenade->SetBounceCount(BounceCount);
        }

        UE_LOG(LogTemp, Log, TEXT("Grenade Launched! Ammo remaining: %d"), AmmoCount);
    }
}

void AGrenadeLaunchers::ReloadWeapon()
{
    AmmoCount = MaxAmmo;
    UE_LOG(LogTemp, Log, TEXT("Reloading Grenade Launcher. Ammo refilled to: %d"), MaxAmmo);
}
