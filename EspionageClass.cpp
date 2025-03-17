// Aegis Protocol - EspionageClass.cpp
// Implements Espionage Mech class with radar disruption and stealth-based combat.

#include "EspionageClass.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "MechCharacter.h"

AEspionageClass::AEspionageClass()
{
    // Default Espionage Mech stats
    MechHealth = 900.0f;  // Lower durability due to lightweight armor
    MovementSpeed = 600.0f;  // Higher mobility for recon operations
    FirepowerMultiplier = 0.85f;  // Slightly reduced firepower (Espionage mechs aren't frontline fighters)

    bRadarJammerActive = false;
    RadarJammerDuration = 10.0f;  // Jammer lasts 10 seconds
    RadarJammerCooldown = 20.0f;  // Cooldown after activation

    ReconPingRadius = 5000.0f;  // 5000 Unreal units detection radius
    ReconPingCooldown = 15.0f;  // 15-second cooldown for recon scan
}

void AEspionageClass::BeginPlay()
{
    Super::BeginPlay();
    ApplyEspionagePerks();
}

void AEspionageClass::ApplyEspionagePerks()
{
    // Espionage Class Perks: Reduced detection time & improved radar efficiency
    RadarDetectionRange *= 1.20f; // +20% increased detection radius
    StealthDetectionTime *= 0.75f; // 25% faster time to hide from enemy radar
}

void AEspionageClass::Attack()
{
    if (EquippedWeapon)
    {
        EquippedWeapon->Fire();
    }
}

void AEspionageClass::ActivateRadarJammer()
{
    if (!bRadarJammerActive)
    {
        bRadarJammerActive = true;

        // Log activation
        UE_LOG(LogTemp, Log, TEXT("Radar Jammer Activated! Enemies' radars are disabled in range."));

        // Disable enemy radar within range
        for (TActorIterator<AMechCharacter> It(GetWorld()); It; ++It)
        {
            AMechCharacter* EnemyMech = *It;
            if (EnemyMech && EnemyMech->GetTeam() != this->GetTeam() && FVector::Dist(GetActorLocation(), EnemyMech->GetActorLocation()) < ReconPingRadius)
            {
                EnemyMech->bIsRadarDisabled = true;
                UE_LOG(LogTemp, Log, TEXT("Enemy radar disabled for mech at %s"), *EnemyMech->GetActorLocation().ToString());
            }
        }

        // Set a timer to reset the ability after duration
        GetWorldTimerManager().SetTimer(RadarJammerCooldownHandle, this, &AEspionageClass::ResetRadarJammer, RadarJammerDuration, false);
    }
}

void AEspionageClass::ResetRadarJammer()
{
    bRadarJammerActive = false;
    UE_LOG(LogTemp, Log, TEXT("Radar Jammer Deactivated"));

    // Re-enable enemy radars
    for (TActorIterator<AMechCharacter> It(GetWorld()); It; ++It)
    {
        AMechCharacter* EnemyMech = *It;
        if (EnemyMech)
        {
            EnemyMech->bIsRadarDisabled = false;
        }
    }
}

void AEspionageClass::ActivateReconPing()
{
    // Check if cooldown is active
    if (GetWorldTimerManager().IsTimerActive(ReconPingCooldownHandle))
    {
        UE_LOG(LogTemp, Log, TEXT("Recon Ping is on cooldown!"));
        return;
    }

    // Log activation
    UE_LOG(LogTemp, Log, TEXT("Recon Ping Activated!"));

    // Reveal enemy positions within range
    for (TActorIterator<AMechCharacter> It(GetWorld()); It; ++It)
    {
        AMechCharacter* EnemyMech = *It;
        if (EnemyMech && EnemyMech->GetTeam() != this->GetTeam() && FVector::Dist(GetActorLocation(), EnemyMech->GetActorLocation()) < ReconPingRadius)
        {
            EnemyMech->bIsVisibleOnRadar = true;
            UE_LOG(LogTemp, Log, TEXT("Enemy mech spotted at %s"), *EnemyMech->GetActorLocation().ToString());
        }
    }

    // Start cooldown
    GetWorldTimerManager().SetTimer(ReconPingCooldownHandle, this, &AEspionageClass::ResetReconPing, ReconPingCooldown, false);
}

void AEspionageClass::ResetReconPing()
{
    UE_LOG(LogTemp, Log, TEXT("Recon Ping cooldown ended."));
}