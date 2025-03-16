#include "MechCharacter.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AMechCharacter::AMechCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsRadarDisabled = false;
    bIsHUDDisabled = false;
}

void AMechCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMechCharacter::DisableRadar(float DisableDuration)
{
    if (!bIsRadarDisabled)
    {
        bIsRadarDisabled = true;
        UE_LOG(LogTemp, Log, TEXT("Radar Disabled!"));

        // Set timer to restore radar after EMP effect expires
        GetWorldTimerManager().SetTimer(
            FTimerHandle(), this, &AMechCharacter::RestoreRadar, DisableDuration, false);
    }
}

void AMechCharacter::RestoreRadar()
{
    bIsRadarDisabled = false;
    UE_LOG(LogTemp, Log, TEXT("Radar Restored!"));
}

void AMechCharacter::DisableHUD(float DisableDuration)
{
    if (!bIsHUDDisabled)
    {
        bIsHUDDisabled = true;
        UE_LOG(LogTemp, Log, TEXT("HUD Disabled!"));

        // Set timer to restore HUD after EMP effect expires
        GetWorldTimerManager().SetTimer(
            FTimerHandle(), this, &AMechCharacter::RestoreHUD, DisableDuration, false);
    }
}

void AMechCharacter::RestoreHUD()
{
    bIsHUDDisabled = false;
    UE_LOG(LogTemp, Log, TEXT("HUD Restored!"));
}
};