#include "AssaultRifles.h"
#include "Engine/World.h"
#include "ProjectileBullet.h"

AAssaultRifles::AAssaultRifles()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default Variant
    AssaultRifleVariant = EAssaultRifleType::FalconAR12;
    SetupWeaponStats();
}

void AAssaultRifles::SetupWeaponStats()
{
    switch (AssaultRifleVariant)
    {
    case EAssaultRifleType::FalconAR12:
        AmmoCount = 40;
        MaxAmmo = 40;
        FireRate = 0.08f;
        Recoil = 0.8f;
        BulletSpread = 2.0f;
        BulletVelocity = 3200.0f;
        break;

    case EAssaultRifleType::BulldogAR18:
        AmmoCount = 30;
        MaxAmmo = 30;
        FireRate = 0.1f;
        Recoil = 1.0f;
        BulletSpread = 2.5f;
        BulletVelocity = 3100.0f;
        break;

    case EAssaultRifleType::DreadnoughtAR22:
        AmmoCount = 25;
        MaxAmmo = 25;
        FireRate = 0.12f;
        Recoil = 1.2f;
        BulletSpread = 3.0f;
        BulletVelocity = 3000.0f;
        break;

    case EAssaultRifleType::TyrantAR30:
        AmmoCount = 20;
        MaxAmmo = 20;
        FireRate = 0.15f;
        Recoil = 1.5f;
        BulletSpread = 3.5f;
        BulletVelocity = 2900.0f;
        break;

    case EAssaultRifleType::WarbringerAR40:
        AmmoCount = 15;
        MaxAmmo = 15;
        FireRate = 0.18f;
        Recoil = 2.0f;
        BulletSpread = 4.0f;
        BulletVelocity = 2800.0f;
        break;
    }
}

void AAssaultRifles::FireWeapon()
{
    if (AmmoCount > 0)
    {
        AmmoCount--;

        float RecoilOffset = FMath::RandRange(-Recoil, Recoil);
        float BulletDeviation = FMath::RandRange(-BulletSpread, BulletSpread);

        FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator MuzzleRotation = GetActorRotation();
        MuzzleRotation.Yaw += RecoilOffset;
        MuzzleRotation.Pitch += BulletDeviation;

        AProjectileBullet* SpawnedBullet = GetWorld()->SpawnActor<AProjectileBullet>(AProjectileBullet::StaticClass(), MuzzleLocation, MuzzleRotation);
        if (SpawnedBullet)
        {
            SpawnedBullet->SetBulletSpeed(BulletVelocity);
        }

        UE_LOG(LogTemp, Log, TEXT("Assault Rifle Fired! Ammo: %d, Recoil: %f, Spread: %f"), AmmoCount, RecoilOffset, BulletDeviation);
    }
}

void AAssaultRifles::ReloadWeapon()
{
    AmmoCount = MaxAmmo;
    UE_LOG(LogTemp, Log, TEXT("Reloading Assault Rifle. Ammo refilled to: %d"), MaxAmmo);
}