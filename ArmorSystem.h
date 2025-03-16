// Aegis Protocol - ArmorSystem.h
// Manages armor plates attached to mech parts (cockpit, weapons, legs) & energy shields

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
    Prototype UMETA(DisplayName = "Prototype Energy Shield")
};

UCLASS()
class AEGISPROTOCOL_API AArmorSystem : public AActor
{
    GENERATED_BODY()

public:
    AArmorSystem();

    virtual void Tick(float DeltaTime) override;
    void TakeDamage(float DamageAmount, FVector ImpactDirection);
    bool IsArmorBroken() const;
    float GetArmorHealth() const;
    float GetWeightImpact() const;
    void ApplyWeightPenalty(class AMechCharacter* Mech);
    bool IsShieldActive() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Armor Properties")
    EArmorType ArmorType;

    UPROPERTY(EditAnywhere, Category = "Armor Properties")
    float MaxArmorHealth;

    UPROPERTY(VisibleAnywhere, Category = "Armor Properties")
    float CurrentArmorHealth;

    UPROPERTY(EditAnywhere, Category = "Armor Properties")
    float DamageReductionPercent; // % of damage absorbed

    UPROPERTY(EditAnywhere, Category = "Armor Properties")
    float WeightImpact; // How much weight it adds to the mech

    UPROPERTY(EditAnywhere, Category = "Prototype Shield")
    bool bShieldActive; // Only applies to Prototype Armor

    UPROPERTY(EditAnywhere, Category = "Prototype Shield")
    float ShieldCooldownTime; // Cooldown before shield reactivates

    UPROPERTY(VisibleAnywhere, Category = "Prototype Shield")
    float ShieldCooldownRemaining;

    UPROPERTY(EditAnywhere, Category = "Prototype Shield")
    FVector ShieldDirection; // Directional protection

    void StartShieldCooldown();
    void UpdateShieldCooldown(float DeltaTime);
};