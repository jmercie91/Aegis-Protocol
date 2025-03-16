#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "GameSessionManager.generated.h"

UCLASS()
class AEGISPROTOCOL_API AGameSessionManager : public AGameSession
{
    GENERATED_BODY()

public:
    AGameSessionManager();

    virtual void BeginPlay() override;

    void StartSession();
    void EndSession();
    void AssignPlayersToClans();
    void TrackPlayerStatus();
    void HandlePlayerReconnection(APlayerController* Player);

    int GetPlayerCount(int Team);
    bool IsPlayerDisconnected(APlayerController* Player);
    bool CanPlayerJoin(); // New function to check if the session is full

private:
    static constexpr int MaxPlayers = 12; // 6v6 max limit
    TArray<APlayerController*> Clan1Players;
    TArray<APlayerController*> Clan2Players;
    TMap<APlayerController*, bool> DisconnectedPlayers;
};