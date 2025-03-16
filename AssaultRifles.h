#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AssaultRifles.generated.h"

UENUM(BlueprintType)
enum class EAssaultRifleType : uint8
{
    FalconAR12 UMETA(DisplayName = "Falcon AR12"),
    BulldogAR18 UMETA(DisplayName = "Bulldog AR18"),
    DreadnoughtAR22 UMETA(DisplayName = "Dreadnought AR22"),
    TyrantAR30 UMETA(DisplayName = "Tyrant AR30"),
    WarbringerAR40 UMETA(DisplayName = "Warbringer AR40")
};

UCLASS()
class AEGISPROTOCOL_API AAssaultRifles : public AActor
{
    GENERATED_BODY()

public:
    AAssaultRifles();
    virtual void Tick(float DeltaTime) override;
    void FireWeapon();
    void ReloadWeapon();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    int32 AmmoCount;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    int32 MaxAmmo;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float FireRate;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float Recoil;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float BulletSpread;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float BulletVelocity;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    TSubclassOf<class AProjectileBullet> BulletClass;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    EAssaultRifleType AssaultRifleVariant;
};