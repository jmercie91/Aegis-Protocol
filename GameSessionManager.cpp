#include "GameSessionManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AGameSessionManager::AGameSessionManager()
{
    Clan1Players.Empty();
    Clan2Players.Empty();
    DisconnectedPlayers.Empty();

    UE_LOG(LogTemp, Log, TEXT("Game Session Manager Initialized"));
}

void AGameSessionManager::BeginPlay()
{
    Super::BeginPlay();
    StartSession();
}

void AGameSessionManager::StartSession()
{
    UE_LOG(LogTemp, Log, TEXT("Game Session Started!"));

    // Initialize clans
    Clan1Players.Empty();
    Clan2Players.Empty();
    DisconnectedPlayers.Empty();

    // Assign players to their respective clans
    AssignPlayersToClans();
}

void AGameSessionManager::EndSession()
{
    UE_LOG(LogTemp, Log, TEXT("Game Session Ended!"));

    // Perform necessary cleanup before transitioning
    Clan1Players.Empty();
    Clan2Players.Empty();
}

void AGameSessionManager::AssignPlayersToClans()
{
    TArray<APlayerController*> AllPlayers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), AllPlayers);

    for (APlayerController* Player : AllPlayers)
    {
        if (Player)
        {
            FString PlayerClan = Player->GetPlayerState<APlayerState>()->GetPlayerName(); // Placeholder for actual clan logic

            if (PlayerClan.StartsWith("Clan1_") && Clan1Players.Num() < 6) // Enforce 6-player max
            {
                Clan1Players.Add(Player);
                UE_LOG(LogTemp, Log, TEXT("Player %s assigned to Clan 1"), *Player->GetName());
            }
            else if (PlayerClan.StartsWith("Clan2_") && Clan2Players.Num() < 6) // Enforce 6-player max
            {
                Clan2Players.Add(Player);
                UE_LOG(LogTemp, Log, TEXT("Player %s assigned to Clan 2"), *Player->GetName());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Player %s could not be assigned (Team Full)"), *Player->GetName());
            }
        }
    }
}

void AGameSessionManager::TrackPlayerStatus()
{
    for (int i = Clan1Players.Num() - 1; i >= 0; i--)
    {
        if (IsPlayerDisconnected(Clan1Players[i]))
        {
            DisconnectedPlayers.Add(Clan1Players[i], true);
            UE_LOG(LogTemp, Warning, TEXT("Player %s disconnected from Clan 1"), *Clan1Players[i]->GetName());
        }
    }

    for (int i = Clan2Players.Num() - 1; i >= 0; i--)
    {
        if (IsPlayerDisconnected(Clan2Players[i]))
        {
            DisconnectedPlayers.Add(Clan2Players[i], true);
            UE_LOG(LogTemp, Warning, TEXT("Player %s disconnected from Clan 2"), *Clan2Players[i]->GetName());
        }
    }
}

void AGameSessionManager::HandlePlayerReconnection(APlayerController* Player)
{
    if (Player && DisconnectedPlayers.Contains(Player))
    {
        DisconnectedPlayers.Remove(Player);
        UE_LOG(LogTemp, Log, TEXT("Player %s reconnected!"), *Player->GetName());
    }
}

int AGameSessionManager::GetPlayerCount(int Team)
{
    return (Team == 1) ? Clan1Players.Num() : Clan2Players.Num();
}

bool AGameSessionManager::IsPlayerDisconnected(APlayerController* Player)
{
    if (!Player)
    {
        return true;
    }

    return !Player->IsLocalPlayerController();
}

bool AGameSessionManager::CanPlayerJoin()
{
    return (Clan1Players.Num() + Clan2Players.Num()) < MaxPlayers;
}