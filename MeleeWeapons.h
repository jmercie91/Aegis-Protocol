// Aegis Protocol - MeleeWeapons.h
// Manages melee weapon mechanics, damage, and knockback

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeWeapons.generated.h"

UENUM(BlueprintType)
enum class EMeleeWeaponType : uint8
{
    Light UMETA(DisplayName = "Light Blade"),
    Heavy UMETA(DisplayName = "Heavy Cleaver"),
    Hammer UMETA(DisplayName = "Shockwave Hammer")
};

UCLASS()
class AEGISPROTOCOL_API AMeleeWeapons : public AActor
{
    GENERATED_BODY()

public:
    AMeleeWeapons();

    virtual void Tick(float DeltaTime) override;
    void PerformMeleeAttack();
    bool CanAttack() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Melee Properties")
    EMeleeWeaponType MeleeType;

    UPROPERTY(EditAnywhere, Category = "Melee Properties")
    float AttackDamage;

    UPROPERTY(EditAnywhere, Category = "Melee Properties")
    float AttackRange;

    UPROPERTY(EditAnywhere, Category = "Melee Properties")
    float AttackCooldown;

    UPROPERTY(EditAnywhere, Category = "Melee Properties")
    float KnockbackForce;

    UPROPERTY(EditAnywhere, Category = "Melee Properties")
    bool bCanAttack;

    void ApplyMeleeDamage(AActor* Target);
    void StartCooldown();
    void EndCooldown();
};
