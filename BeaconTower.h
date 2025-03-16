// Aegis Protocol - BeaconTower.h
// Implements beacon capture mechanics, recapture logic, and visibility effects

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeaconTower.generated.h"

UCLASS()
class AEGISPROTOCOL_API ABeaconTower : public AActor
{
    GENERATED_BODY()

public:
    ABeaconTower();

    virtual void Tick(float DeltaTime) override;
    void BeginCapture(class AMechCharacter* CapturingMech);
    void ContinueCapture(class AMechCharacter* CapturingMech);
    void CompleteCapture();
    void ResetCapture();
    void RevealMechOnRadar(class AMechCharacter* Mech);
    bool IsWithinCaptureRadius(class AMechCharacter* Mech) const;
    int32 GetOwningTeam() const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Beacon Properties")
    int32 OwningTeam;

    UPROPERTY(EditAnywhere, Category = "Capture Properties")
    float CaptureTimeRequired;

    UPROPERTY(VisibleAnywhere, Category = "Capture Properties")
    float CurrentCaptureTime;

    UPROPERTY(EditAnywhere, Category = "Capture Properties")
    float CaptureRadius;

    UPROPERTY()
    class AMechCharacter* CapturingMech;

    FTimerHandle CaptureTimerHandle;
};