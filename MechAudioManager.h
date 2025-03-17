// Aegis Protocol - MechAudioManager.h
// Manages all mech-related sound effects, including movement, weapons, destruction, radar alerts, and UI sounds.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "MechAudioManager.generated.h"

UENUM(BlueprintType)
enum class EUISoundType : uint8
{
    ButtonClick UMETA(DisplayName = "Button Click"),
    MatchStart UMETA(DisplayName = "Match Start"),
    Warning UMETA(DisplayName = "Warning Beep"),
    Victory UMETA(DisplayName = "Victory Sound"),
    Defeat UMETA(DisplayName = "Defeat Sound")
};

UENUM(BlueprintType)
enum class EWeaponStatusSoundType : uint8
{
    LowAmmo UMETA(DisplayName = "Low Ammo Warning"),
    Reloading UMETA(DisplayName = "Reloading Sound")
};

UENUM(BlueprintType)
enum class ERadarAlertType : uint8
{
    EnemyDetected UMETA(DisplayName = "Enemy Detected"),
    StealthJammerNearby UMETA(DisplayName = "Stealth Jammer Nearby")
};

UCLASS()
class AEGISPROTOCOL_API AMechAudioManager : public AActor
{
    GENERATED_BODY()

public:
    AMechAudioManager();

protected:
    virtual void BeginPlay() override;

public:
    /** ?? Mech Movement Sounds */
    UFUNCTION(BlueprintCallable, Category = "Audio|Movement")
    void PlayMovementSound(FString MovementType, FString TerrainType);

    /** ?? Weapon Fire Sounds */
    UFUNCTION(BlueprintCallable, Category = "Audio|Weapons")
    void PlayWeaponFireSound(FString WeaponType);

    /** ?? Battlefield Ambience */
    UFUNCTION(BlueprintCallable, Category = "Audio|Environment")
    void PlayBattlefieldAmbience(FString EnvironmentType);

    /** ? UI Sounds (Notifications, Buttons, etc.) */
    UFUNCTION(BlueprintCallable, Category = "Audio|UI")
    void PlayUISound(EUISoundType UISound);

    /** ?? Weapon Status Sounds (Reloading, Low Ammo) */
    UFUNCTION(BlueprintCallable, Category = "Audio|Weapons")
    void PlayWeaponStatusSound(EWeaponStatusSoundType WeaponStatus);

    /** ?? Radar Alert Sounds (Enemy Detection, Stealth Jammer Nearby) */
    UFUNCTION(BlueprintCallable, Category = "Audio|Radar")
    void PlayRadarAlertSound(ERadarAlertType RadarAlert);

    /** ?? Mech Damage and Destruction */
    UFUNCTION(BlueprintCallable, Category = "Audio|Combat")
    void PlayDamageSound();

    UFUNCTION(BlueprintCallable, Category = "Audio|Combat")
    void PlayDestructionSound();

protected:
    /** ?? Internal function to play sounds */
    void InternalPlaySound(USoundCue* SoundCue);

    /** ?? Movement Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|Movement")
    USoundCue* LightFootstepSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Movement")
    USoundCue* HeavyFootstepSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Movement")
    USoundCue* TrackedMovementSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Movement")
    USoundCue* WheeledMovementSound;

    /** ?? Weapon Fire Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* SniperFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* AssaultRifleFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* ShotgunFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* MachineGunFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* RocketLauncherFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* GrenadeLauncherFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* LockOnWeaponFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* MeleeWeaponHitSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* EMPWeaponSound;

    /** ?? Weapon Status Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* LowAmmoWarningSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* ReloadingSound;

    /** ?? Battlefield Ambient Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|Environment")
    USoundCue* DistantGunfireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Environment")
    USoundCue* ExplosionsInBackground;

    UPROPERTY(EditAnywhere, Category = "Audio|Environment")
    USoundCue* RadioChatterSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Environment")
    USoundCue* MechMarchingSound;

    /** ? UI Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* UIButtonClickSound;

    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* MatchStartSound;

    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* WarningBeepSound;

    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* VictorySound;

    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* DefeatSound;

    /** ?? Radar Alerts */
    UPROPERTY(EditAnywhere, Category = "Audio|Radar")
    USoundCue* EnemyDetectedSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Radar")
    USoundCue* StealthJammerSound;

    /** ?? Mech Damage & Destruction */
    UPROPERTY(EditAnywhere, Category = "Audio|Combat")
    USoundCue* ExplosionSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Combat")
    USoundCue* MechDestructionSound;
};// Aegis Protocol - MechAudioManager.h
// Manages all mech-related sound effects, including movement, weapons, destruction, radar alerts, and UI sounds.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "MechAudioManager.generated.h"

UENUM(BlueprintType)
enum class EUISoundType : uint8
{
    ButtonClick UMETA(DisplayName = "Button Click"),
    MatchStart UMETA(DisplayName = "Match Start"),
    Warning UMETA(DisplayName = "Warning Beep"),
    Victory UMETA(DisplayName = "Victory Sound"),
    Defeat UMETA(DisplayName = "Defeat Sound")
};

UENUM(BlueprintType)
enum class EWeaponStatusSoundType : uint8
{
    LowAmmo UMETA(DisplayName = "Low Ammo Warning"),
    Reloading UMETA(DisplayName = "Reloading Sound")
};

UENUM(BlueprintType)
enum class ERadarAlertType : uint8
{
    EnemyDetected UMETA(DisplayName = "Enemy Detected"),
    StealthJammerNearby UMETA(DisplayName = "Stealth Jammer Nearby")
};

UCLASS()
class AEGISPROTOCOL_API AMechAudioManager : public AActor
{
    GENERATED_BODY()

public:
    AMechAudioManager();

protected:
    virtual void BeginPlay() override;

public:
    /** ?? Mech Movement Sounds */
    UFUNCTION(BlueprintCallable, Category = "Audio|Movement")
    void PlayMovementSound(FString MovementType, FString TerrainType);

    /** ?? Weapon Fire Sounds */
    UFUNCTION(BlueprintCallable, Category = "Audio|Weapons")
    void PlayWeaponFireSound(FString WeaponType);

    /** ?? Battlefield Ambience */
    UFUNCTION(BlueprintCallable, Category = "Audio|Environment")
    void PlayBattlefieldAmbience(FString EnvironmentType);

    /** ? UI Sounds (Notifications, Buttons, etc.) */
    UFUNCTION(BlueprintCallable, Category = "Audio|UI")
    void PlayUISound(EUISoundType UISound);

    /** ?? Weapon Status Sounds (Reloading, Low Ammo) */
    UFUNCTION(BlueprintCallable, Category = "Audio|Weapons")
    void PlayWeaponStatusSound(EWeaponStatusSoundType WeaponStatus);

    /** ?? Radar Alert Sounds (Enemy Detection, Stealth Jammer Nearby) */
    UFUNCTION(BlueprintCallable, Category = "Audio|Radar")
    void PlayRadarAlertSound(ERadarAlertType RadarAlert);

    /** ?? Mech Damage and Destruction */
    UFUNCTION(BlueprintCallable, Category = "Audio|Combat")
    void PlayDamageSound();

    UFUNCTION(BlueprintCallable, Category = "Audio|Combat")
    void PlayDestructionSound();

protected:
    /** ?? Internal function to play sounds */
    void InternalPlaySound(USoundCue* SoundCue);

    /** ?? Movement Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|Movement")
    USoundCue* LightFootstepSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Movement")
    USoundCue* HeavyFootstepSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Movement")
    USoundCue* TrackedMovementSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Movement")
    USoundCue* WheeledMovementSound;

    /** ?? Weapon Fire Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* SniperFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* AssaultRifleFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* ShotgunFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* MachineGunFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* RocketLauncherFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* GrenadeLauncherFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* LockOnWeaponFireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* MeleeWeaponHitSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* EMPWeaponSound;

    /** ?? Weapon Status Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* LowAmmoWarningSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Weapons")
    USoundCue* ReloadingSound;

    /** ?? Battlefield Ambient Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|Environment")
    USoundCue* DistantGunfireSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Environment")
    USoundCue* ExplosionsInBackground;

    UPROPERTY(EditAnywhere, Category = "Audio|Environment")
    USoundCue* RadioChatterSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Environment")
    USoundCue* MechMarchingSound;

    /** ? UI Sounds */
    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* UIButtonClickSound;

    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* MatchStartSound;

    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* WarningBeepSound;

    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* VictorySound;

    UPROPERTY(EditAnywhere, Category = "Audio|UI")
    USoundCue* DefeatSound;

    /** ?? Radar Alerts */
    UPROPERTY(EditAnywhere, Category = "Audio|Radar")
    USoundCue* EnemyDetectedSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Radar")
    USoundCue* StealthJammerSound;

    /** ?? Mech Damage & Destruction */
    UPROPERTY(EditAnywhere, Category = "Audio|Combat")
    USoundCue* ExplosionSound;

    UPROPERTY(EditAnywhere, Category = "Audio|Combat")
    USoundCue* MechDestructionSound;
};