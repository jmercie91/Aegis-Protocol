#include "Shotguns.h"
#include "Engine/World.h"
#include "ProjectileBullet.h"

AShotguns::AShotguns()
{
    PrimaryActorTick.bCanEverTick = true;
    ShotgunVariant = EShotgunType::WardenSG4;
    SetupWeaponStats();
}

void AShotguns::SetupWeaponStats()
{
    switch (ShotgunVariant)
    {
    case EShotgunType::WardenSG4:
        AmmoCount = 8;
        MaxAmmo = 8;
        FireRate = 1.0f;
        SpreadAngle = 15.0f;
        BulletVelocity = 1500.0f;
        break;

    case EShotgunType::HellstormSG8:
        AmmoCount = 6;
        MaxAmmo = 6;
        FireRate = 1.2f;
        SpreadAngle = 20.0f;
        BulletVelocity = 1400.0f;
        break;

    case EShotgunType::BrutalizerSG10:
        AmmoCount = 5;
        MaxAmmo = 5;
        FireRate = 1.5f;
        SpreadAngle = 12.0f;
        BulletVelocity = 1300.0f;
        break;

    case EShotgunType::MaulerSG14:
        AmmoCount = 4;
        MaxAmmo = 4;
        FireRate = 1.8f;
        SpreadAngle = 10.0f;
        BulletVelocity = 1200.0f;
        break;
    }
}

void AShotguns::FireWeapon()
{
    if (AmmoCount > 0)
    {
        AmmoCount--;

        for (int i = 0; i < 8; i++) // Simulating pellet spread
        {
            float BulletDeviation = FMath::RandRange(-SpreadAngle, SpreadAngle);
            FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
            FRotator MuzzleRotation = GetActorRotation();
            MuzzleRotation.Pitch += BulletDeviation;

            AProjectileBullet* SpawnedBullet = GetWorld()->SpawnActor<AProjectileBullet>(AProjectileBullet::StaticClass(), MuzzleLocation, MuzzleRotation);
            if (SpawnedBullet)
            {
                SpawnedBullet->SetBulletSpeed(BulletVelocity);
            }
        }

        UE_LOG(LogTemp, Log, TEXT("Shotgun fired! Ammo: %d"), AmmoCount);
    }
}

void AShotguns::ReloadWeapon()
{
    AmmoCount = MaxAmmo;
    UE_LOG(LogTemp, Log, TEXT("Reloading Shotgun. Ammo refilled to: %d"), MaxAmmo);
}