// Aegis Protocol - ScoutClass.cpp
// Implements Scout Class abilities: High-speed movement, stealth mode, and enemy detection.

#include "ScoutClass.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "HUDManager.h"
#include "DynamicWeather.h"
#include "MultiplayerManager.h"

AScoutClass::AScoutClass()
{
    // Set default values for scout abilities
    BoostSpeedMultiplier = 1.5f; // 50% speed increase
    BoostDuration = 3.0f; // Lasts for 3 seconds
    StealthDuration = 5.0f; // Stealth lasts for 5 seconds
    EnemyDetectionRange = 1000.0f; // Base detection range
    bIsStealthed = false;
}

void AScoutClass::BeginPlay()
{
    Super::BeginPlay();
}

void AScoutClass::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ScanForEnemies();
}

// Activate temporary speed boost
void AScoutClass::ActivateBoost()
{
    if (!GetCharacterMovement()) return;

    GetCharacterMovement()->MaxWalkSpeed *= BoostSpeedMultiplier;
    UE_LOG(LogTemp, Log, TEXT("Scout activated speed boost!"));

    // Set a timer to reset speed after duration
    GetWorldTimerManager().SetTimer(BoostTimerHandle, this, &AScoutClass::EndBoost, BoostDuration, false);
}

// Reset speed after boost duration ends
void AScoutClass::EndBoost()
{
    if (!GetCharacterMovement()) return;

    GetCharacterMovement()->MaxWalkSpeed /= BoostSpeedMultiplier;
    UE_LOG(LogTemp, Log, TEXT("Scout boost ended, speed reset."));
}

// Activate stealth mode (temporary radar invisibility)
void AScoutClass::ActivateStealth()
{
    if (bIsStealthed) return;

    bIsStealthed = true;
    SetActorHiddenInGame(true);
    UE_LOG(LogTemp, Log, TEXT("Scout activated stealth mode!"));

    // Set a timer to deactivate stealth
    GetWorldTimerManager().SetTimer(StealthTimerHandle, this, &AScoutClass::DeactivateStealth, StealthDuration, false);
}

// Deactivate stealth mode
void AScoutClass::DeactivateStealth()
{
    bIsStealthed = false;
    SetActorHiddenInGame(false);
    UE_LOG(LogTemp, Log, TEXT("Scout stealth mode ended!"));
}

// Scan for enemies within range
void AScoutClass::ScanForEnemies()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMechCharacter::StaticClass(), FoundActors);

    // Adjust detection range based on weather conditions
    float AdjustedRange = EnemyDetectionRange;
    ADynamicWeather* WeatherSystem = Cast<ADynamicWeather>(UGameplayStatics::GetActorOfClass(GetWorld(), ADynamicWeather::StaticClass()));

    if (WeatherSystem)
    {
        AdjustedRange -= WeatherSystem->GetDetectionPenalty();
        AdjustedRange = FMath::Clamp(AdjustedRange, 500.0f, EnemyDetectionRange); // Min range limit
    }

    for (AActor* Actor : FoundActors)
    {
        AMechCharacter* Mech = Cast<AMechCharacter>(Actor);
        if (Mech && Mech != this && Mech->GetTeamID() != GetTeamID()) // Ensure it's an enemy
        {
            float Distance = FVector::Dist(GetActorLocation(), Mech->GetActorLocation());

            if (Distance <= AdjustedRange)
            {
                UE_LOG(LogTemp, Log, TEXT("Enemy detected at distance: %.2f"), Distance);

                // Send detection signal to HUD
                AHUDManager* HUDManager = Cast<AHUDManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AHUDManager::StaticClass()));
                if (HUDManager)
                {
                    HUDManager->DisplayEnemyOnMinimap(Mech->GetActorLocation());
                }

                // Sync detection across all clients
                AMultiplayerManager* MultiplayerManager = Cast<AMultiplayerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMultiplayerManager::StaticClass()));
                if (MultiplayerManager)
                {
                    MultiplayerManager->BroadcastEnemyDetection(Mech->GetActorLocation());
                }
            }
        }
    }
}