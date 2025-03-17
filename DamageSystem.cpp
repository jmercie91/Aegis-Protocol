// Aegis Protocol - DamageSystem.cpp
// Implements all damage-related mechanics in Aegis Protocol.

#include "DamageSystem.h"
#include "MechCharacter.h"
#include "ArmorSystem.h"

ADamageSystem::ADamageSystem()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADamageSystem::BeginPlay()
{
    Super::BeginPlay();
}

void ADamageSystem::ApplyDamage(AActor* Target, const FDamageInfo& DamageInfo)
{
    if (!Target) return;

    // Check if the target is a MechCharacter
    AMechCharacter* Mech = Cast<AMechCharacter>(Target);
    if (Mech)
    {
        float DamageAmount = DamageInfo.BaseDamage;

        // Process armor interactions before applying damage
        ProcessArmorDamage(Mech, DamageAmount, DamageInfo.DamageType);

        // Apply the final damage
        Mech->TakeDamage(DamageAmount, FDamageEvent(), DamageInfo.DamageInstigator->GetInstigatorController(), this);

        // Log damage event
        UE_LOG(LogTemp, Log, TEXT("%s took %.2f damage from %s"), *Mech->GetName(), DamageAmount, *DamageInfo.DamageInstigator->GetName());

        // If a component reaches 0 HP, destroy it
        if (Mech->IsComponentDestroyed())
        {
            DestroyComponent(Mech);
        }
    }
}

void ADamageSystem::ProcessArmorDamage(AActor* Target, float& DamageAmount, EDamageType DamageType)
{
    AMechCharacter* Mech = Cast<AMechCharacter>(Target);
    if (!Mech) return;

    // Check if the mech has active armor
    if (Mech->ActiveArmor && Mech->ActiveArmor->GetArmorHealth() > 0)
    {
        float ArmorHealth = Mech->ActiveArmor->GetArmorHealth();

        // Reduce damage based on armor type
        switch (DamageType)
        {
        case EDamageType::Projectile:
            DamageAmount *= 0.75f; // 25% damage reduction
            break;
        case EDamageType::Explosion:
            DamageAmount *= 0.50f; // 50% damage reduction
            break;
        case EDamageType::Energy:
            DamageAmount *= 0.60f; // Energy weapons partially bypass armor
            break;
        case EDamageType::EMP:
            DamageAmount *= 0.25f; // EMP does almost no damage to armor
            break;
        case EDamageType::Melee:
            DamageAmount *= 0.90f; // Melee mostly bypasses armor
            break;
        }

        // Deduct armor health first
        float RemainingArmor = ArmorHealth - DamageAmount;
        Mech->ActiveArmor->SetArmorHealth(FMath::Max(0.0f, RemainingArmor));

        // If armor is fully destroyed, remove it
        if (Mech->ActiveArmor->GetArmorHealth() <= 0)
        {
            UE_LOG(LogTemp, Log, TEXT("%s's armor is destroyed!"), *Mech->GetName());
            Mech->DestroyArmor();
        }
    }
}

void ADamageSystem::DestroyComponent(AActor* TargetComponent)
{
    if (TargetComponent)
    {
        UE_LOG(LogTemp, Log, TEXT("%s component destroyed!"), *TargetComponent->GetName());
        TargetComponent->Destroy();
    }
}