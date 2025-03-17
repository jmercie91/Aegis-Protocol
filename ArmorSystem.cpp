// Aegis Protocol - ArmorSystem.cpp
// Implements armor durability, energy shield cooldowns, and damage logic.

#include "ArmorSystem.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

AArmorSystem::AArmorSystem()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default armor settings
    Armor.ArmorType = EArmorType::Medium;
    Armor.MaxDurability = 1000.0f;
    Armor.CurrentDurability = Armor.MaxDurability;
    Armor.Weight = 50.0f;
    Armor.bIsDestroyed = false;

    // Shield settings
    bIsShieldActive = false;
    ShieldCooldownTime = 30.0f;  // Cooldown when destroyed
    ShieldRegenTime = 15.0f;     // Cooldown when toggled off manually
}

void AArmorSystem::BeginPlay()
{
    Super::BeginPlay();
}

void AArmorSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AArmorSystem::TakeDamage(float DamageAmount)
{
    if (bIsShieldActive)
    {
        UE_LOG(LogTemp, Log, TEXT("Shield absorbed damage: %f"), DamageAmount);
        DeactivatePrototypeShield();
        return;
    }

    Armor.CurrentDurability -= DamageAmount;

    if (Armor.CurrentDurability <= 0)
    {
        Armor.bIsDestroyed = true;
        Armor.CurrentDurability = 0;
        UE_LOG(LogTemp, Log, TEXT("Armor Destroyed!"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Armor took damage: %f | Remaining: %f"), DamageAmount, Armor.CurrentDurability);
    }
}

void AArmorSystem::RegenerateArmor()
{
    if (!Armor.bIsDestroyed)
    {
        Armor.CurrentDurability = Armor.MaxDurability;
        UE_LOG(LogTemp, Log, TEXT("Armor fully regenerated!"));
    }
}

void AArmorSystem::ActivatePrototypeShield()
{
    if (!bIsShieldActive && !GetWorld()->GetTimerManager().IsTimerActive(ShieldCooldownTimer))
    {
        bIsShieldActive = true;
        UE_LOG(LogTemp, Log, TEXT("Prototype Shield Activated!"));
    }
}

void AArmorSystem::DeactivatePrototypeShield()
{
    bIsShieldActive = false;
    UE_LOG(LogTemp, Log, TEXT("Prototype Shield Deactivated!"));

    GetWorld()->GetTimerManager().SetTimer(
        ShieldCooldownTimer,
        this,
        &AArmorSystem::ResetShieldCooldown,
        Armor.bIsDestroyed ? ShieldCooldownTime : ShieldRegenTime,
        false
    );
}

bool AArmorSystem::IsArmorDestroyed() const
{
    return Armor.bIsDestroyed;
}

void AArmorSystem::ResetShieldCooldown()
{
    UE_LOG(LogTemp, Log, TEXT("Prototype Shield Ready for Activation!"));
}