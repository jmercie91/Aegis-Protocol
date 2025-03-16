#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LegConfiguration.generated.h"

// Enum for Different Mech Leg Configurations
UENUM(BlueprintType)
enum class ELegType : uint8
{
    FalconL1      UMETA(DisplayName = "Falcon-L1 (Light Bipedal)"),
    StriderL2     UMETA(DisplayName = "Strider-L2 (Balanced Bipedal)"),
    JuggernautL3  UMETA(DisplayName = "Juggernaut-L3 (Heavy Bipedal)"),

    CheetahQ1     UMETA(DisplayName = "Cheetah-Q1 (Light Quadruped)"),
    SentinelQ2    UMETA(DisplayName = "Sentinel-Q2 (Balanced Quadruped)"),
    ColossusQ3    UMETA(DisplayName = "Colossus-Q3 (Heavy Quadruped)"),

    WidowmakerH1  UMETA(DisplayName = "Widowmaker-H1 (Light Hexapod)"),
    TitanH2       UMETA(DisplayName = "Titan-H2 (Balanced Hexapod)"),
    BehemothH3    UMETA(DisplayName = "Behemoth-H3 (Heavy Hexapod)"),

    ViperT1       UMETA(DisplayName = "Viper-T1 (Light Tracked)"),
    GoliathT2     UMETA(DisplayName = "Goliath-T2 (Heavy Tracked)"),

    RaptorW1      UMETA(DisplayName = "Raptor-W1 (Light Wheeled)"),
    NomadW2       UMETA(DisplayName = "Nomad-W2 (All-Terrain Wheeled)")
};

UCLASS()
class AEGISPROTOCOL_API ALegConfiguration : public AActor
{
    GENERATED_BODY()

public:
    ALegConfiguration();
    virtual void Tick(float DeltaTime) override;

    void SetLegType(ELegType NewLegType);
    float GetSpeedModifier() const;
    float GetTurnSpeed() const;
    float GetWeightCapacity() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Leg Configuration")
    ELegType LegType;

    UPROPERTY(EditAnywhere, Category = "Leg Stats")
    float SpeedModifier;

    UPROPERTY(EditAnywhere, Category = "Leg Stats")
    float TurnSpeed;

    UPROPERTY(EditAnywhere, Category = "Leg Stats")
    float WeightCapacity;

    void UpdateLegStats();
};