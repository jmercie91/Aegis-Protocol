#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockOnWeapons.generated.h"

UENUM(BlueprintType)
enum class ELockOnWeaponType : uint8
{
    StingerL1 UMETA(DisplayName = "Stinger L1"),
    HawkeyeL2 UMETA(DisplayName = "Hawkeye L2"),
    VortexL3 UMETA(DisplayName = "Vortex L3")
};

UCLASS()
class AEGISPROTOCOL_API ALockOnWeapons : public AActor
{
    GENERATED_BODY()

public:
    ALockOnWeapons();
    virtual void Tick(float DeltaTime) override;
    void FireWeapon();
    void ReloadWeapon();
    void SetupWeaponStats();
    void TrackTarget(AActor* Target);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    int32 AmmoCount;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    int32 MaxAmmo;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float LockOnTime;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float ExplosionRadius;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    ELockOnWeaponType LockOnWeaponVariant;

    AActor* LockedTarget;
};