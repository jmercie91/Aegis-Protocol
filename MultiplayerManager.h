// Aegis Protocol - MultiplayerManager.h
// Manages matchmaking, team battles, weather synchronization, and enemy detection sync across all players.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicWeather.h"
#include "MultiplayerManager.generated.h"

UCLASS()
class AEGISPROTOCOL_API AMultiplayerManager : public AActor
{
    GENERATED_BODY()

public:
    AMultiplayerManager();

protected:
    virtual void BeginPlay() override;

public:
    // **Matchmaking Functions**

    // Queue a clan for battle at a specific battlefield
    UFUNCTION(BlueprintCallable, Category = "Matchmaking")
    void QueueClanForBattle(FString BattlefieldName, int32 TeamID);

    // Find an opponent for the battlefield
    void FindOpponentForBattle(FString BattlefieldName);

    // Start a battle between two clans
    void StartClanBattle(FString BattlefieldName, int32 Team1ID, int32 Team2ID);

    // End the battle and update control point ownership
    void EndClanBattle(FString BattlefieldName, int32 WinningTeamID);

    // Updates control point ownership after a match
    void UpdateBattlefieldOwnership(FString BattlefieldName, int32 NewOwnerTeam);

    // Notify teams that the match has started
    void NotifyTeamsOfMatchStart(int32 Team1ID, int32 Team2ID, FString BattlefieldName);

    // **Weather Synchronization**

    // Determines and sets weather for the current battle session
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSetWeatherForBattle(FString BattlefieldName);

    // Applies the chosen weather effects to all players
    UFUNCTION(NetMulticast, Reliable)
    void ApplyWeatherEffectsToAllPlayers(EWeatherCondition ChosenWeather);

    // **Enemy Detection Synchronization**

    // Sync detected enemies across all players in a match
    UFUNCTION(NetMulticast, Reliable)
    void SyncEnemyDetection(ACharacter* DetectedEnemy, FVector EnemyLocation);

private:
    // Stores queued teams for each battlefield
    TMap<FString, int32> QueuedTeams;
};