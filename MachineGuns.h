// C#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MachineGuns.generated.h"

UENUM(BlueprintType)
enum class EMachineGunType : uint8
{
    JackalMG5 UMETA(DisplayName = "Jackal MG5"),
    HavocMG12 UMETA(DisplayName = "Havoc MG12"),
    GoliathMG20 UMETA(DisplayName = "Goliath MG20"),
    OverlordMG30 UMETA(DisplayName = "Overlord MG30"),
    TitanMG40 UMETA(DisplayName = "Titan MG40")
};

UCLASS()
class AEGISPROTOCOL_API AMachineGuns : public AActor
{
    GENERATED_BODY()

public:
    AMachineGuns();
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
};