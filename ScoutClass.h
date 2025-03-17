// Aegis Protocol - ScoutClass.h
// Defines the Scout class abilities, including speed boost, stealth, and enemy detection.

#pragma once

#include "CoreMinimal.h"
#include "MechCharacter.h"
#include "ScoutClass.generated.h"

UCLASS()
class AEGISPROTOCOL_API AScoutClass : public AMechCharacter
{
    GENERATED_BODY()

public:
    // Constructor
    AScoutClass();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Speed boost activation
    UFUNCTION(BlueprintCallable, Category = "Scout Abilities")
    void ActivateBoost();

    // End speed boost
    UFUNCTION(BlueprintCallable, Category = "Scout Abilities")
    void EndBoost();

    // Activate stealth mode
    UFUNCTION(BlueprintCallable, Category = "Scout Abilities")
    void ActivateStealth();

    // Deactivate stealth mode
    UFUNCTION(BlueprintCallable, Category = "Scout Abilities")
    void DeactivateStealth();

    // Scan for nearby enemies
    UFUNCTION(BlueprintCallable, Category = "Scout Abilities")
    void ScanForEnemies();

private:
    // Speed boost properties
    UPROPERTY(EditAnywhere, Category = "Scout Abilities")
    float BoostSpeedMultiplier;

    UPROPERTY(EditAnywhere, Category = "Scout Abilities")
    float BoostDuration;

    FTimerHandle BoostTimerHandle;

    // Stealth properties
    UPROPERTY(EditAnywhere, Category = "Scout Abilities")
    float StealthDuration;

    FTimerHandle StealthTimerHandle;

    bool bIsStealthed;

    // Enemy detection properties
    UPROPERTY(EditAnywhere, Category = "Scout Abilities")
    float EnemyDetectionRange;
};