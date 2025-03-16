#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementSystem.generated.h"

// Enum for Different Leg Types
UENUM(BlueprintType)
enum class EMechLegType : uint8
{
    Bipedal      UMETA(DisplayName = "Bipedal"),
    Quadruped    UMETA(DisplayName = "Quadruped"),
    Hexapod      UMETA(DisplayName = "Hexapod"),
    Tracked      UMETA(DisplayName = "Tracked"),
    Wheeled      UMETA(DisplayName = "Wheeled")
};

UCLASS()
class AEGISPROTOCOL_API AMovementSystem : public AActor
{
    GENERATED_BODY()

public:
    AMovementSystem();
    virtual void Tick(float DeltaTime) override;

    void SetLegType(EMechLegType NewLegType);
    float GetMaxSpeed() const;
    float GetTurnRate() const;
    float GetWeightCapacity() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Movement")
    EMechLegType LegType;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MaxSpeed;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnRate;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float WeightCapacity;

    void UpdateMovementStats();
};

