// Aegis Protocol - GameModeManager.cpp
// Implements game loop, match structure, and win conditions

#include "GameModeManager.h"
#include "Kismet/GameplayStatics.h"
#include "BeaconTower.h"
#include "MechCharacter.h"

AGameModeManager::AGameModeManager()
{
    PrimaryActorTick.bCanEverTick = true;
    Team1Score = 0;
    Team2Score = 0;
    MatchTimer = 900.0f; // 15 minutes
    Team1BaseHealth = 100000.0f;
    Team2BaseHealth = 100000.0f;
}

void AGameModeManager::BeginPlay()
{
    Super::BeginPlay();
    StartMatch();
}

void AGameModeManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MatchTimer -= DeltaTime;
    CheckWinConditions();
}

void AGameModeManager::StartMatch()
{
    // Initialize match state
    Team1Score = 0;
    Team2Score = 0;
    MatchTimer = 900.0f; // 15 minutes
    Team1BaseHealth = 100000.0f;
    Team2BaseHealth = 100000.0f;

    UE_LOG(LogTemp, Log, TEXT("Match Started!"));
}

void AGameModeManager::EndMatch()
{
    DeclareWinner();
    UE_LOG(LogTemp, Log, TEXT("Match Ended!"));
}

void AGameModeManager::CheckWinConditions()
{
    // Condition 1: Eliminate all enemy mechs
    if (Team1Score >= 100 || Team2Score >= 100)
    {
        EndMatch();
        return;
    }

    // Condition 2: Destroy enemy home base
    if (IsBaseDestroyed(1) || IsBaseDestroyed(2))
    {
        EndMatch();
        return;
    }

    // Condition 3: Control more beacon towers when time runs out
    if (MatchTimer <= 0.0f)
    {
        int Team1Beacons = GetControlledBeaconCount(1);
        int Team2Beacons = GetControlledBeaconCount(2);

        if (Team1Beacons > Team2Beacons)
        {
            Team1Score += 10; // Bonus for beacon control
        }
        else if (Team2Beacons > Team1Beacons)
        {
            Team2Score += 10;
        }

        EndMatch();
    }
}

bool AGameModeManager::IsBaseDestroyed(int Team)
{
    if (Team == 1)
    {
        return Team1BaseHealth <= 0;
    }
    else if (Team == 2)
    {
        return Team2BaseHealth <= 0;
    }
    return false;
}

void AGameModeManager::DeclareWinner()
{
    if (Team1Score > Team2Score)
    {
        UE_LOG(LogTemp, Log, TEXT("Team 1 Wins!"));
        AwardFlawlessVictoryBonus(1);
    }
    else if (Team2Score > Team1Score)
    {
        UE_LOG(LogTemp, Log, TEXT("Team 2 Wins!"));
        AwardFlawlessVictoryBonus(2);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Match is tied - Entering Sudden Death!"));
        int RandomBeaconID = FMath::RandRange(1, 5);
        UE_LOG(LogTemp, Log, TEXT("Sudden Death - Capture Beacon Tower %d!"), RandomBeaconID);
    }
}

int AGameModeManager::GetControlledBeaconCount(int Team)
{
    int BeaconCount = 0;

    for (TActorIterator<ABeaconTower> It(GetWorld()); It; ++It)
    {
        if (It->GetOwningTeam() == Team)
        {
            BeaconCount++;
        }
    }

    return BeaconCount;
}

void AGameModeManager::AwardFlawlessVictoryBonus(int WinningTeam)
{
    bool bNoDeaths = true;
    bool bBaseDestroyed = false;
    bool bAllEnemyMechsDestroyed = true;
    bool bBeaconControlWin = false;

    // Check if any mech on the winning team has died
    for (TActorIterator<AMechCharacter> It(GetWorld()); It; ++It)
    {
        if (It->GetTeam() == WinningTeam && It->IsDead())
        {
            bNoDeaths = false;
            break;
        }
    }

    // Check if the victory condition was destroying the enemy base
    if (IsBaseDestroyed(WinningTeam == 1 ? 2 : 1))
    {
        bBaseDestroyed = true;
    }

    // Check if the victory condition was destroying all enemy mechs
    for (TActorIterator<AMechCharacter> It(GetWorld()); It; ++It)
    {
        if (It->GetTeam() != WinningTeam && !It->IsDead())
        {
            bAllEnemyMechsDestroyed = false;
            break;
        }
    }

    // Check if the victory was due to beacon control
    if (MatchTimer <= 0.0f)
    {
        int TeamBeacons = GetControlledBeaconCount(WinningTeam);
        int OpponentBeacons = GetControlledBeaconCount(WinningTeam == 1 ? 2 : 1);

        if (TeamBeacons > OpponentBeacons)
        {
            bBeaconControlWin = true;
        }
    }

    // Assign Flawless Victory Bonus based on win condition
    if (bNoDeaths)
    {
        if (bBaseDestroyed)
        {
            UE_LOG(LogTemp, Log, TEXT("Flawless Victory (Base Destruction)! Team %d receives +30 points!"), WinningTeam);
            if (WinningTeam == 1) Team1Score += 30;
            else Team2Score += 30;
        }
        else if (bBeaconControlWin)
        {
            UE_LOG(LogTemp, Log, TEXT("Flawless Victory (Beacon Control)! Team %d receives +10 points!"), WinningTeam);
            if (WinningTeam == 1) Team1Score += 10;
            else Team2Score += 10;
        }
        else if (bAllEnemyMechsDestroyed)
        {
            UE_LOG(LogTemp, Log, TEXT("Flawless Victory (Full Enemy Wipe)! Team %d receives +20 points!"), WinningTeam);
            if (WinningTeam == 1) Team1Score += 20;
            else Team2Score += 20;
        }
    }
}