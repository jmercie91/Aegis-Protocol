#include "SniperRifles.h"
#include "Engine/World.h"
#include "ProjectileBullet.h"

ASniperRifles::ASniperRifles()
{
    PrimaryActorTick.bCanEverTick = true;
    SniperVariant = ESniperType::VultureS1;
    SetupWeaponStats();
    bIsZoomedIn = false;
}

void ASniperRifles::SetupWeaponStats()
{
    switch (SniperVariant)
    {
    case ESniperType::VultureS1:
        AmmoCount = 7;
        MaxAmmo = 7;
        FireRate = 1.2f;
        BulletVelocity = 4000.0f;
        ZoomLevel = 2.0f;
        break;

    case ESniperType::MarksmanX2:
        AmmoCount = 5;
        MaxAmmo = 5;
        FireRate = 1.5f;
        BulletVelocity = 4200.0f;
        ZoomLevel = 2.5f;
        break;

    case ESniperType::ReaperLR3:
        AmmoCount = 4;
        MaxAmmo = 4;
        FireRate = 2.0f;
        BulletVelocity = 4400.0f;
        ZoomLevel = 3.0f;
        break;

    case ESniperType::BlackoutX4:
        AmmoCount = 6;
        MaxAmmo = 6;
        FireRate = 1.8f;
        BulletVelocity = 4600.0f;
        ZoomLevel = 3.5f;
        break;

    case ESniperType::WidowmakerX5:
        AmmoCount = 9;
        MaxAmmo = 9;
        FireRate = 2.5f;
        BulletVelocity = 4800.0f;
        ZoomLevel = 4.0f;
        break;
    }
}

void ASniperRifles::BeginPlay()
{
    Super::BeginPlay();
}

void ASniperRifles::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASniperRifles::FireWeapon()
{
    if (AmmoCount > 0)
    {
        AmmoCount--;

        FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator MuzzleRotation = GetActorRotation();

        AProjectileBullet* SpawnedBullet = GetWorld()->SpawnActor<AProjectileBullet>(AProjectileBullet::StaticClass(), MuzzleLocation, MuzzleRotation);
        if (SpawnedBullet)
        {
            SpawnedBullet->SetBulletSpeed(BulletVelocity);
        }

        UE_LOG(LogTemp, Log, TEXT("Sniper Rifle Fired! Ammo: %d"), AmmoCount);
    }
}

void ASniperRifles::ReloadWeapon()
{
    AmmoCount = MaxAmmo;
    UE_LOG(LogTemp, Log, TEXT("Reloading Sniper Rifle. Ammo refilled to: %d"), MaxAmmo);
}

void ASniperRifles::ToggleZoom(bool bZoomIn)
{
    bIsZoomedIn = bZoomIn;
    if (bZoomIn)
    {
        UE_LOG(LogTemp, Log, TEXT("Zooming in to %fx"), ZoomLevel);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Zooming out"));
    }
}