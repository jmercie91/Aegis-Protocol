#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RocketLaunchers.generated.h"

UENUM(BlueprintType)
enum class ERocketLauncherType : uint8
{
    BarrageRL6 UMETA(DisplayName = "Barrage RL6"),
    TyphoonRL9 UMETA(DisplayName = "Typhoon RL9"),
    DoombringerRL15 UMETA(DisplayName = "Doombringer RL15"),
    OblivionRL20 UMETA(DisplayName = "Oblivion RL20"),
    JudgmentRL25 UMETA(DisplayName = "Judgment RL25")
};

UCLASS()
class AEGISPROTOCOL_API ARocketLaunchers : public AActor
{
    GENERATED_BODY()

public:
    ARocketLaunchers();
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
    float ReloadTime;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float ExplosionRadius;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    ERocketLauncherType RocketLauncherVariant;
};
