#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SniperRifles.generated.h"

UENUM(BlueprintType)
enum class ESniperType : uint8
{
    VultureS1 UMETA(DisplayName = "Vulture S1"),
    MarksmanX2 UMETA(DisplayName = "Marksman X2"),
    ReaperLR3 UMETA(DisplayName = "Reaper LR3"),
    BlackoutX4 UMETA(DisplayName = "Blackout X4"),
    WidowmakerX5 UMETA(DisplayName = "Widowmaker X5")
};

UCLASS()
class AEGISPROTOCOL_API ASniperRifles : public AActor
{
    GENERATED_BODY()

public:
    ASniperRifles();
    virtual void Tick(float DeltaTime) override;
    void FireWeapon();
    void ReloadWeapon();
    void SetupWeaponStats();
    void ToggleZoom(bool bZoomIn);

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
    float BulletVelocity;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    float ZoomLevel;

    UPROPERTY(EditAnywhere, Category = "Weapon Stats")
    ESniperType SniperVariant;

    bool bIsZoomedIn;
};