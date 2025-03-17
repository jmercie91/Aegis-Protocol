// Aegis Protocol - SupportClass.cpp
// Implements support abilities: Healing allies, deploying shields, and energy regeneration.

#include "SupportClass.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ASupportClass::ASupportClass()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize support ability properties
    HealAmount = 50.0f;
    HealCooldown = 5.0f;
    ShieldDuration = 6.0f;
    ShieldHealth = 75.0f;
    EnergyRegenAmount = 25.0f;
    EnergyRegenCooldown = 8.0f;

    bCanHeal = true;
    bCanRegenEnergy = true;
}

void ASupportClass::BeginPlay()
{
    Super::BeginPlay();
}

void ASupportClass::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Heal an ally within range
void ASupportClass::HealAlly(ACharacter* Ally)
{
    if (!Ally || !bCanHeal) return;

    // Increase ally's health
    float CurrentHealth = Ally->GetHealth();
    float MaxHealth = Ally->GetMaxHealth();
    float NewHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
    Ally->SetHealth(NewHealth);

    UE_LOG(LogTemp, Log, TEXT("Support Class healed ally! New Health: %.2f"), NewHealth);

    // Start cooldown
    bCanHeal = false;
    GetWorldTimerManager().SetTimer(HealCooldownTimer, this, &ASupportClass::ResetHealCooldown, HealCooldown, false);
}

void ASupportClass::ResetHealCooldown()
{
    bCanHeal = true;
}

// Deploy a temporary shield on an ally
void ASupportClass::DeployShield(ACharacter* Ally)
{
    if (!Ally) return;

    Ally->ActivateShield(ShieldHealth, ShieldDuration);
    UE_LOG(LogTemp, Log, TEXT("Support Class deployed a shield on an ally! Shield HP: %.2f"), ShieldHealth);
}

// Regenerate energy for an ally
void ASupportClass::RegenerateEnergy(ACharacter* Ally)
{
    if (!Ally || !bCanRegenEnergy) return;

    float CurrentEnergy = Ally->GetEnergy();
    float MaxEnergy = Ally->GetMaxEnergy();
    float NewEnergy = FMath::Clamp(CurrentEnergy + EnergyRegenAmount, 0.0f, MaxEnergy);
    Ally->SetEnergy(NewEnergy);

    UE_LOG(LogTemp, Log, TEXT("Support Class regenerated energy for an ally! New Energy: %.2f"), NewEnergy);

    // Start cooldown
    bCanRegenEnergy = false;
    GetWorldTimerManager().SetTimer(EnergyRegenTimer, this, &ASupportClass::ResetEnergyRegenCooldown, EnergyRegenCooldown, false);
}

void ASupportClass::ResetEnergyRegenCooldown()
{
    bCanRegenEnergy = true;
}