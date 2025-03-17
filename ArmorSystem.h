// Aegis Protocol - ArmorSystem.h
// Manages armor plating, durability, and prototype energy shield cooldown.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmorSystem.generated.h"

UENUM(BlueprintType)
enum class EArmorType : uint8
{
    Light UMETA(DisplayName = "Light Armor"),
    Medium UMETA(DisplayName = "Medium Armor"),
    Heavy UMETA(DisplayName = "Heavy Armor"),
    PrototypeShield UMETA(DisplayName = "Prototype Energy Shield")
};

USTRUCT(BlueprintType)
struct FArmorStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
    EArmorType ArmorType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
    float MaxDurability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
    float CurrentDurability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
    float Weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
    bool bIsDestroyed;
};

UCLASS()
class AEGISPROTOCOL_API AArmorSystem : public AActor
{
    GENERATED_BODY()

public:
    AArmorSystem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Armor")
    void TakeDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Armor")
    void RegenerateArmor();

    UFUNCTION(BlueprintCallable, Category = "Armor")
    void ActivatePrototypeShield();

    UFUNCTION(BlueprintCallable, Category = "Armor")
    void DeactivatePrototypeShield();

    UFUNCTION(BlueprintCallable, Category = "Armor")
    bool IsArmorDestroyed() const;

private:
    UPROPERTY(EditAnywhere, Category = "Armor Config")
    FArmorStats Armor;

    UPROPERTY(EditAnywhere, Category = "Shield Config")
    bool bIsShieldActive;

    UPROPERTY(EditAnywhere, Category = "Shield Config")
    float ShieldCooldownTime;

    UPROPERTY(EditAnywhere, Category = "Shield Config")
    float ShieldRegenTime;

    UFUNCTION()
    void ResetShieldCooldown();

    FTimerHandle ShieldCooldownTimer;
};