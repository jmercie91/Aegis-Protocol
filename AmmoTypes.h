// Aegis Protocol - AmmoTypes.h
// Defines multiple ammo types and their effects on gameplay.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AmmoTypes.generated.h"

// Enum defining different types of ammo in the game
UENUM(BlueprintType)
enum class EAmmoType : uint8
{
    Standard UMETA(DisplayName = "Standard"),
    ArmorPiercing UMETA(DisplayName = "Armor Piercing"),
    Incendiary UMETA(DisplayName = "Incendiary"),
    Explosive UMETA(DisplayName = "Explosive"),
    EMP UMETA(DisplayName = "EMP"),
    Plasma UMETA(DisplayName = "Plasma")
};

UCLASS(Blueprintable)
class AEGISPROTOCOL_API UAmmoTypes : public UObject
{
    GENERATED_BODY()

public:
    UAmmoTypes();

    // Gets the base damage modifier for the ammo type
    UFUNCTION(BlueprintCallable, Category = "Ammo")
    static float GetDamageModifier(EAmmoType AmmoType);

    // Gets any special effects the ammo type applies
    UFUNCTION(BlueprintCallable, Category = "Ammo")
    static FString GetAmmoEffect(EAmmoType AmmoType);
};

