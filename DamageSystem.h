// Aegis Protocol - DamageSystem.h
// Manages all damage handling, including armor, health, and destruction logic.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageSystem.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
    Projectile UMETA(DisplayName = "Projectile"),
    Explosion UMETA(DisplayName = "Explosion"),
    Energy UMETA(DisplayName = "Energy"),
    EMP UMETA(DisplayName = "EMP"),
    Melee UMETA(DisplayName = "Melee")
};

USTRUCT(BlueprintType)
struct FDamageInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float BaseDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    EDamageType DamageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    AActor* DamageInstigator;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FVector HitLocation;
};

UCLASS()
class AEGISPROTOCOL_API ADamageSystem : public AActor
{
    GENERATED_BODY()

public:
    ADamageSystem();

    // Apply damage to a mech or its components
    void ApplyDamage(AActor* Target, const FDamageInfo& DamageInfo);

protected:
    virtual void BeginPlay() override;

private:
    // Handles logic for armor vs. health
    void ProcessArmorDamage(AActor* Target, float& DamageAmount, EDamageType DamageType);

    // Destroys a component when health reaches 0
    void DestroyComponent(AActor* TargetComponent);
};

