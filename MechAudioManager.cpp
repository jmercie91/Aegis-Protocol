// Aegis Protocol - MechAudioManager.cpp
// Implements all mech-related sound effects, including movement, weapons, destruction, ambient sounds, and UI feedback.

#include "MechAudioManager.h"
#include "Kismet/GameplayStatics.h"

AMechAudioManager::AMechAudioManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMechAudioManager::BeginPlay()
{
    Super::BeginPlay();
}

// Plays movement sounds based on the mech's movement type and terrain
void AMechAudioManager::PlayMovementSound(FString MovementType, FString TerrainType)
{
    USoundCue* SelectedSound = nullptr;

    if (MovementType == "Bipedal")
    {
        SelectedSound = LightFootstepSound;
    }
    else if (MovementType == "Quadruped" || MovementType == "Hexapod")
    {
        SelectedSound = HeavyFootstepSound;
    }
    else if (MovementType == "Tracked")
    {
        SelectedSound = TrackedMovementSound;
    }
    else if (MovementType == "Wheeled")
    {
        SelectedSound = WheeledMovementSound;
    }

    if (SelectedSound)
    {
        InternalPlaySound(SelectedSound);
    }
}

// Plays weapon fire sound based on the weapon type
void AMechAudioManager::PlayWeaponFireSound(FString WeaponType)
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

    if (SelectedSound)
    {
        InternalPlaySound(SelectedSound);
    }
}

// Plays battlefield ambient sounds based on environment
void AMechAudioManager::PlayBattlefieldAmbience(FString EnvironmentType)
{
    USoundCue* SelectedSound = nullptr;

    if (EnvironmentType == "Urban")
    {
        SelectedSound = DistantGunfireSound;
    }
    else if (EnvironmentType == "Desert" || EnvironmentType == "Jungle")
    {
        SelectedSound = ExplosionsInBackground;
    }
    else if (EnvironmentType == "Arctic")
    {
        SelectedSound = RadioChatterSound;
    }
    else if (EnvironmentType == "Battlefield")
    {
        SelectedSound = MechMarchingSound;
    }

    if (SelectedSound)
    {
        InternalPlaySound(SelectedSound);
    }
}

// Adjusts audio mixing dynamically based on intensity
void AMechAudioManager::AdjustAudioMixing(float Intensity)
{
    float VolumeMultiplier = FMath::Clamp(Intensity, 0.5f, 2.0f);

    if (UGameplayStatics::GetGameInstance(this))
    {
        UGameplayStatics::SetGlobalTimeDilation(GetWorld(), VolumeMultiplier);
    }
}

// Plays damage sound when the mech is hit
void AMechAudioManager::PlayDamageSound()
{
    if (ExplosionSound)
    {
        InternalPlaySound(ExplosionSound);
    }
}

// Plays destruction sound when the mech is destroyed
void AMechAudioManager::PlayDestructionSound()
{
    if (MechDestructionSound)
    {
        InternalPlaySound(MechDestructionSound);
    }
}

// **🔊 New - Plays UI Sound for Notifications**
void AMechAudioManager::PlayUISound(EUISoundType UISound)
{
    USoundCue* SelectedSound = nullptr;

    switch (UISound)
    {
    case EUISoundType::ButtonClick:
        SelectedSound = UIButtonClickSound;
        break;
    case EUISoundType::MatchStart:
        SelectedSound = MatchStartSound;
        break;
    case EUISoundType::Warning:
        SelectedSound = WarningBeepSound;
        break;
    case EUISoundType::Victory:
        SelectedSound = VictorySound;
        break;
    case EUISoundType::Defeat:
        SelectedSound = DefeatSound;
        break;
    }

    if (SelectedSound)
    {
        InternalPlaySound(SelectedSound);
    }
}

// **🔊 New - Plays low ammo or reload sound**
void AMechAudioManager::PlayWeaponStatusSound(EWeaponStatusSoundType WeaponStatus)
{
    USoundCue* SelectedSound = nullptr;

    switch (WeaponStatus)
    {
    case EWeaponStatusSoundType::LowAmmo:
        SelectedSound = LowAmmoWarningSound;
        break;
    case EWeaponStatusSoundType::Reloading:
        SelectedSound = ReloadingSound;
        break;
    }

    if (SelectedSound)
    {
        InternalPlaySound(SelectedSound);
    }
}

// **🔊 New - Plays Radar Detection Alert**
void AMechAudioManager::PlayRadarAlertSound(ERadarAlertType RadarAlert)
{
    USoundCue* SelectedSound = nullptr;

    switch (RadarAlert)
    {
    case ERadarAlertType::EnemyDetected:
        SelectedSound = EnemyDetectedSound;
        break;
    case ERadarAlertType::StealthJammerNearby:
        SelectedSound = StealthJammerSound;
        break;
    }

    if (SelectedSound)
    {
        InternalPlaySound(SelectedSound);
    }
}

// Internal function to play sounds
void AMechAudioManager::InternalPlaySound(USoundCue* SoundCue)
{
    if (SoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(this, SoundCue, GetActorLocation());
    }
}