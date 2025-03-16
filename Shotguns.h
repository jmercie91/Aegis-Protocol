#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shotguns.generated.h"

UENUM(BlueprintType)
enum class EShotgunType : uint8
{
    WardenSG4 UMETA(DisplayName = "Warden SG4"),
    HellstormSG8 UMETA(DisplayName = "Hellstorm SG8"),
    BrutalizerSG10 UMETA(DisplayName = "Brutalizer SG10"),
    MaulerSG14 UMETA(DisplayName = "Mauler SG14")
};

UCLASS()
class AEGISPROTOCOL_API AShotguns : public AActor
{
    GENERATED_BODY()

public:
    AShotguns();
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
    float SpreadAngle;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float BulletVelocity;
};