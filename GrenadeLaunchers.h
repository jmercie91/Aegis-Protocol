#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrenadeLaunchers.generated.h"

UENUM(BlueprintType)
enum class EGrenadeLauncherType : uint8
{
    RattlesnakeGL3 UMETA(DisplayName = "Rattlesnake GL3"),
    AnacondaGL7 UMETA(DisplayName = "Anaconda GL7"),
    PythonGL10 UMETA(DisplayName = "Python GL10"),
    BasiliskGL16 UMETA(DisplayName = "Basilisk GL16"),
    VenomGL20 UMETA(DisplayName = "Venom GL20")
};

UCLASS()
class AEGISPROTOCOL_API AGrenadeLaunchers : public AActor
{
    GENERATED_BODY()

public:
    AGrenadeLaunchers();
    virtual void Tick(float DeltaTime) override;
    void FireWeapon();
    void ReloadWeapon();
    void SetupWeaponStats();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    int32 AmmoCount;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    int32 MaxAmmo;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float ExplosionRadius;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float BounceCount;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    EGrenadeLauncherType GrenadeLauncherVariant;
};

