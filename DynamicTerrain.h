// Aegis Protocol - DynamicTerrain.h
// Handles terrain-based movement speed, weapon accuracy, and armor effects.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicTerrain.generated.h"

UENUM(BlueprintType)
enum class ETerrainType : uint8
{
    Grassland UMETA(DisplayName = "Grassland"),
    Desert UMETA(DisplayName = "Desert"),
    Snow UMETA(DisplayName = "Snow"),
    Swamp UMETA(DisplayName = "Swamp"),
    Rocky UMETA(DisplayName = "Rocky Terrain"),
    Urban UMETA(DisplayName = "Urban"),
    Water UMETA(DisplayName = "Water"),
    Mud UMETA(DisplayName = "Mud")
};

UCLASS()
class AEGISPROTOCOL_API ADynamicTerrain : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADynamicTerrain();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Applies terrain effects to the mech
    UFUNCTION(BlueprintCallable, Category = "Terrain Effects")
    void ApplyTerrainEffects(class AMechCharacter* Mech, ETerrainType TerrainType);

private:
    // Modifiers for terrain effect calculations
    UPROPERTY(EditAnywhere, Category = "Terrain Effects")
    float SpeedModifier;

    UPROPERTY(EditAnywhere, Category = "Terrain Effects")
    float AccuracyModifier;

    UPROPERTY(EditAnywhere, Category = "Terrain Effects")
    float ArmorEffectivenessModifier;
};

