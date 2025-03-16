#include "LockOnWeapons.h"
#include "Engine/World.h"
#include "ProjectileMissile.h"
#include "Kismet/GameplayStatics.h"

ALockOnWeapons::ALockOnWeapons()
{
    PrimaryActorTick.bCanEverTick = true;
    LockOnWeaponVariant = ELockOnWeaponType::StingerL1;
    SetupWeaponStats();
}

void ALockOnWeapons::SetupWeaponStats()
{
    switch (LockOnWeaponVariant)
    {
    case ELockOnWeaponType::StingerL1:
        AmmoCount = 4;
        MaxAmmo = 4;
        LockOnTime = 1.5f;
        ExplosionRadius = 250.0f;
        break;

    case ELockOnWeaponType::HawkeyeL2:
        AmmoCount = 3;
        MaxAmmo = 3;
        LockOnTime = 2.0f;
        ExplosionRadius = 275.0f;
        break;

    case ELockOnWeaponType::VortexL3:
        AmmoCount = 2;
        MaxAmmo = 2;
        LockOnTime = 2.5f;
        ExplosionRadius = 300.0f;
        break;
    }
}

void ALockOnWeapons::BeginPlay()
{
    Super::BeginPlay();
}

void ALockOnWeapons::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALockOnWeapons::TrackTarget(AActor* Target)
{
    if (Target)
    {
        LockedTarget = Target;
        UE_LOG(LogTemp, Log, TEXT("Locking onto target: %s"), *Target->GetName());
    }
}

void ALockOnWeapons::FireWeapon()
{
    if (AmmoCount > 0 && LockedTarget)
    {
        AmmoCount--;

        FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator MuzzleRotation = GetActorRotation();

        AProjectileMissile* SpawnedMissile = GetWorld()->SpawnActor<AProjectileMissile>(AProjectileMissile::StaticClass(), MuzzleLocation, MuzzleRotation);
        if (SpawnedMissile)
        {
            SpawnedMissile->SetTarget(LockedTarget);
        }

        UE_LOG(LogTemp, Log, TEXT("Lock-On Weapon Fired! Ammo remaining: %d"), AmmoCount);
    }
}

void ALockOnWeapons::ReloadWeapon()
{
    AmmoCount = MaxAmmo;
    UE_LOG(LogTemp, Log, TEXT("Reloading Lock-On Weapon. Ammo refilled to: %d"), MaxAmmo);
}