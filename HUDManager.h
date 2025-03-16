// Aegis Protocol - HUDManager.h
// Handles UI elements like targeting, radar, and mech health

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDManager.generated.h"

UCLASS()
class AEGISPROTOCOL_API AHUDManager : public AHUD
{
    GENERATED_BODY()

public:
    AHUDManager();
    virtual void DrawHUD() override;

private:
    void DisplayMechHealth();
    void DisplayAmmoCount();
    void DrawTargetingReticle();
};