// Aegis Protocol - SupportClass.h
// Implements support abilities: Healing allies, deploying shields, and energy regeneration.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SupportClass.generated.h"

UCLASS()
class AEGISPROTOCOL_API ASupportClass : public ACharacter
{
    GENERATED_BODY()

public:
    ASupportClass();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Healing ability
    UFUNCTION(BlueprintCallable, Category = "Support Abilities")
    void HealAlly(ACharacter* Ally);

    // Deploy temporary shield on an ally
    UFUNCTION(BlueprintCallable, Category = "Support Abilities")
    void DeployShield(ACharacter* Ally);

    // Regenerate energy for an ally
    UFUNCTION(BlueprintCallable, Category = "Support Abilities")
    void RegenerateEnergy(ACharacter* Ally);

private:
    // Healing properties
    UPROPERTY(EditAnywhere, Category = "Healing")
    float HealAmount;

    UPROPERTY(EditAnywhere, Category = "Healing")
    float HealCooldown;

    UPROPERTY(EditAnywhere, Category = "Shield")
    float ShieldDuration;

    UPROPERTY(EditAnywhere, Category = "Shield")
    float ShieldHealth;

    UPROPERTY(EditAnywhere, Category = "Energy")
    float EnergyRegenAmount;

    UPROPERTY(EditAnywhere, Category = "Energy")
    float EnergyRegenCooldown;

    FTimerHandle HealCooldownTimer;
    FTimerHandle EnergyRegenTimer;

    bool bCanHeal;
    bool bCanRegenEnergy;

    void ResetHealCooldown();
    void ResetEnergyRegenCooldown();
};