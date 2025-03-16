// Aegis Protocol - ArmorSystem.cpp
// Implements armor durability, directional energy shields, weight system, and damage absorption

#include "ArmorSystem.h"
#include "TimerManager.h"
#include "MechCharacter.h"

AArmorSystem::AArmorSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    ArmorType = EArmorType::Medium;
    bShieldActive = false;
    ShieldCooldownTime = 100.0f; // 1 minute cooldown
    ShieldCooldownRemaining = 0.0f;

    // Define armor stats based on type
    switch (ArmorType)
    {
    case EArmorType::Light:
        MaxArmorHealth = 100.0f;
        DamageReductionPercent = 10.0f;
        WeightImpact = 5.0f;
        break;
    case EArmorType::Medium:
        MaxArmorHealth = 250.0f;
        DamageReductionPercent = 25.0f;
        WeightImpact = 15.0f;
        break;
    case EArmorType::Heavy:
        MaxArmorHealth = 500.0f;
        DamageReductionPercent = 50.0f;
        WeightImpact = 30.0f;
        break;
    case EArmorType::Prototype:
        MaxArmorHealth = 350.0f;
        DamageReductionPercent = 40.0f;
        WeightImpact = 20.0f;
        bShieldActive = true;
        break;
    }

    CurrentArmorHealth = MaxArmorHealth;
}

void AArmorSystem::BeginPlay()
{
    Super::BeginPlay();
}

void AArmorSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bShieldActive && ArmorType == EArmorType::Prototype)
    {
        UpdateShieldCooldown(DeltaTime);
    }
}

void AArmorSystem::TakeDamage(float DamageAmount, FVector ImpactDirection)
{
    if (IsArmorBroken())
    {
        return; // Armor is destroyed, no longer providing protection
    }

    if (ArmorType == EArmorType::Prototype && bShieldActive)
    {
        FVector Forward = GetActorForwardVector();

        if (FVector::DotProduct(Forward, ImpactDirection) > 0.5f)
        {
            UE_LOG(LogTemp, Log, TEXT("Prototype Shield Blocked Damage!"));
            return; // Shield blocks attack from the front
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Prototype Shield Failed - Hit from behind!"));
            bShieldActive = false;
            StartShieldCooldown();
        }
    }

    float DamageToApply = DamageAmount * ((100.0f - DamageReductionPercent) / 100.0f);
    CurrentArmorHealth -= DamageToApply;

    if (CurrentArmorHealth <= 0)
    {
        CurrentArmorHealth = 0;
        UE_LOG(LogTemp, Warning, TEXT("Armor is permanently destroyed!"));
        Destroy(); // Armor is fully destroyed and removed from the mech
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Armor took damage: %.2f | Remaining Armor: %.2f"), DamageToApply, CurrentArmorHealth);
    }
}

bool AArmorSystem::IsArmorBroken() const
{
    return CurrentArmorHealth <= 0;
}

float AArmorSystem::GetArmorHealth() const
{
    return CurrentArmorHealth;
}

float AArmorSystem::GetWeightImpact() const
{
    return WeightImpact;
}

void AArmorSystem::ApplyWeightPenalty(AMechCharacter* Mech)
{
    if (Mech)
    {
        float SpeedPenalty = WeightImpact * 0.05f; // Example: Each 10 weight reduces speed by 5%
        Mech->ModifySpeed(-SpeedPenalty);
    }
}

bool AArmorSystem::IsShieldActive() const
{
    return bShieldActive;
}

void AArmorSystem::StartShieldCooldown()
{
    ShieldCooldownRemaining = ShieldCooldownTime;
    UE_LOG(LogTemp, Log, TEXT("Prototype Shield Deactivated - Cooldown Started"));
}

void AArmorSystem::UpdateShieldCooldown(float DeltaTime)
{
    if (ShieldCooldownRemaining > 0)
    {
        ShieldCooldownRemaining -= DeltaTime;

        if (ShieldCooldownRemaining <= 0)
        {
            bShieldActive = true;
            UE_LOG(LogTemp, Log, TEXT("Prototype Shield Reactivated!"));
        }
    }
}