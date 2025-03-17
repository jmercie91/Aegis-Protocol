// Aegis Protocol - WeaponAudioManager.h
// Manages all weapon-related sounds including firing, reloads, impacts, and explosions.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "WeaponAudioManager.generated.h"

UCLASS()
class AEGISPROTOCOL_API AWeaponAudioManager : public AActor
{
    GENERATED_BODY()

public:
    AWeaponAudioManager();

protected:
    virtual void BeginPlay() override;

public:
    // Function to play weapon firing sounds based on weapon type
    UFUNCTION(BlueprintCallable, Category = "Weapon Audio")
    void PlayWeaponFireSound(FString WeaponType);

    // Function to play reload sounds
    UFUNCTION(BlueprintCallable, Category = "Weapon Audio")
    void PlayReloadSound(FString WeaponType);

    // Function to play impact sounds
    UFUNCTION(BlueprintCallable, Category = "Weapon Audio")
    void PlayImpactSound(FString SurfaceType);

    // Function to play explosion sounds
    UFUNCTION(BlueprintCallable, Category = "Weapon Audio")
    void PlayExplosionSound();

    // Function to play overheating sounds
    UFUNCTION(BlueprintCallable, Category = "Weapon Audio")
    void PlayOverheatSound();

private:
    // Maps for storing weapon sounds
    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* SniperFireSound;

    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* AssaultRifleFireSound;

    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* ShotgunFireSound;

    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* MachineGunFireSound;

    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* RocketLauncherFireSound;

    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* GrenadeLauncherFireSound;

    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* LockOnWeaponFireSound;

    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* MeleeWeaponHitSound;

    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* EMPWeaponSound;

    // Reload sounds
    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* ReloadSound;

    // Impact sounds
    UPROPERTY(EditAnywhere, Category = "Impact Sounds")
    USoundCue* MetalImpactSound;

    UPROPERTY(EditAnywhere, Category = "Impact Sounds")
    USoundCue* ConcreteImpactSound;

    UPROPERTY(EditAnywhere, Category = "Impact Sounds")
    USoundCue* WoodImpactSound;

    // Explosion sounds
    UPROPERTY(EditAnywhere, Category = "Explosion Sounds")
    USoundCue* ExplosionSound;

    // Overheat sound
    UPROPERTY(EditAnywhere, Category = "Weapon Sounds")
    USoundCue* OverheatSound;

    // Internal function to play sounds
    void InternalPlaySound(USoundCue* SoundCue);
};