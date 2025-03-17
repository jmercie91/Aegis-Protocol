// Aegis Protocol - WeaponAudioManager.cpp
// Implements weapon sound effects including firing, reloading, impacts, and explosions.

#include "WeaponAudioManager.h"
#include "Kismet/GameplayStatics.h"

AWeaponAudioManager::AWeaponAudioManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AWeaponAudioManager::BeginPlay()
{
    Super::BeginPlay();
}

// Plays weapon firing sounds based on the weapon type
void AWeaponAudioManager::PlayWeaponFireSound(FString WeaponType)
{
    USoundCue* SelectedSound = nullptr;

    if (WeaponType == "Sniper")
    {
        SelectedSound = SniperFireSound;
    }
    else if (WeaponType == "AssaultRifle")
    {
        SelectedSound = AssaultRifleFireSound;
    }
    else if (WeaponType == "Shotgun")
    {
        SelectedSound = ShotgunFireSound;
    }
    else if (WeaponType == "MachineGun")
    {
        SelectedSound = MachineGunFireSound;
    }
    else if (WeaponType == "RocketLauncher")
    {
        SelectedSound = RocketLauncherFireSound;
    }
    else if (WeaponType == "GrenadeLauncher")
    {
        SelectedSound = GrenadeLauncherFireSound;
    }
    else if (WeaponType == "LockOnWeapon")
    {
        SelectedSound = LockOnWeaponFireSound;
    }
    else if (WeaponType == "MeleeWeapon")
    {
        SelectedSound = MeleeWeaponHitSound;
    }
    else if (WeaponType == "EMPWeapon")
    {
        SelectedSound = EMPWeaponSound;
    }

    InternalPlaySound(SelectedSound);
}

// Plays reload sounds for the given weapon type
void AWeaponAudioManager::PlayReloadSound(FString WeaponType)
{
    if (ReloadSound)
    {
        InternalPlaySound(ReloadSound);
    }
}

// Plays impact sounds based on the surface type
void AWeaponAudioManager::PlayImpactSound(FString SurfaceType)
{
    USoundCue* SelectedSound = nullptr;

    if (SurfaceType == "Metal")
    {
        SelectedSound = MetalImpactSound;
    }
    else if (SurfaceType == "Concrete")
    {
        SelectedSound = ConcreteImpactSound;
    }
    else if (SurfaceType == "Wood")
    {
        SelectedSound = WoodImpactSound;
    }

    InternalPlaySound(SelectedSound);
}

// Plays explosion sounds
void AWeaponAudioManager::PlayExplosionSound()
{
    if (ExplosionSound)
    {
        InternalPlaySound(ExplosionSound);
    }
}

// Plays weapon overheating sounds
void AWeaponAudioManager::PlayOverheatSound()
{
    if (OverheatSound)
    {
        InternalPlaySound(OverheatSound);
    }
}

// Internal function to play sounds
void AWeaponAudioManager::InternalPlaySound(USoundCue* SoundCue)
{
    if (SoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(this, SoundCue, GetActorLocation());
    }
}