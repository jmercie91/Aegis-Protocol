// Aegis Protocol - GameModeManager.h
// Handles game loop, match structure, and win conditions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeManager.generated.h"

UCLASS()
class AEGISPROTOCOL_API AGameModeManager : public AGameModeBase
{
    GENERATED_BODY()

public:
    AGameModeManager();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void StartMatch();
    void EndMatch();
    void CheckWinConditions();
    void AwardFlawlessVictoryBonus(int WinningTeam);

private:
    int32 Team1Score;
    int32 Team2Score;
    float MatchTimer;
    float Team1BaseHealth;
    float Team2BaseHealth;

    void DeclareWinner();
    bool IsBaseDestroyed(int Team);
    int GetControlledBeaconCount(int Team);
};