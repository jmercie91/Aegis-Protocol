#include "MachineGuns.h"
#include "Engine/World.h"
#include "ProjectileBullet.h"

AMachineGuns::AMachineGuns()
{
    PrimaryActorTick.bCanEverTick = true;
    MachineGunVariant = EMachineGunType::JackalMG5;
    SetupWeaponStats();
}

void AMachineGuns::SetupWeaponStats()
{
    switch (MachineGunVariant)
    {
    case EMachineGunType::JackalMG5:
        AmmoCount = 100;
        MaxAmmo = 100;
        FireRate = 0.08f;
        Recoil = 1.2f;
        BulletVelocity = 3200.0f;
        break;
    case EMachineGunType::HavocMG12:
        AmmoCount = 80;
        MaxAmmo = 80;
        FireRate = 0.1f;
        Recoil = 1.5f;
        BulletVelocity = 3100.0f;
        break;
    case EMachineGunType::GoliathMG20:
        AmmoCount = 60;
        MaxAmmo = 60;
        FireRate = 0.12f;
        Recoil = 1.8f;
        BulletVelocity = 3000.0f;
        break;
    case EMachineGunType::OverlordMG30:
        AmmoCount = 40;
        MaxAmmo = 40;
        FireRate = 0.14f;
        Recoil = 2.2f;
        BulletVelocity = 2900.0f;
        break;
    case EMachineGunType::TitanMG40:
        AmmoCount = 30;
        MaxAmmo = 30;
        FireRate = 0.18f;
        Recoil = 2.5f;
        BulletVelocity = 2800.0f;
        break;
    }
}

void AMachineGuns::FireWeapon()
{
    if (AmmoCount > 0)
    {
        AmmoCount--;

        float RecoilOffset = FMath::RandRange(-Recoil, Recoil);
        FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator MuzzleRotation = GetActorRotation();
        MuzzleRotation.Yaw += RecoilOffset;

        AProjectileBullet* SpawnedBullet = GetWorld()->SpawnActor<AProjectileBullet>(AProjectileBullet::StaticClass(), MuzzleLocation, MuzzleRotation);
        if (SpawnedBullet)
        {
            SpawnedBullet->SetBulletSpeed(BulletVelocity);
        }

        UE_LOG(LogTemp, Log, TEXT("Machine Gun Fired! Ammo: %d, Recoil: %f"), AmmoCount, RecoilOffset);
    }
}

void AMachineGuns::ReloadWeapon()
{
    AmmoCount = MaxAmmo;
    UE_LOG(LogTemp, Log, TEXT("Reloading Machine Gun. Ammo refilled to: %d"), MaxAmmo);
}