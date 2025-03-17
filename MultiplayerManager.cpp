// Aegis Protocol - MultiplayerManager.cpp
// Implements matchmaking logic, team assignment, battle session handling, weather synchronization, and enemy detection sync.

#include "MultiplayerManager.h"
#include "Kismet/GameplayStatics.h"
#include "MapManager.h"
#include "HUDManager.h"
#include "DynamicWeather.h"
#include "MinimapWidget.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

AMultiplayerManager::AMultiplayerManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMultiplayerManager::BeginPlay()
{
    Super::BeginPlay();
}

// Adds a clan to the queue for a battle at a specific battlefield
void AMultiplayerManager::QueueClanForBattle(FString BattlefieldName, int32 TeamID)
{
    if (!QueuedTeams.Contains(BattlefieldName))
    {
        QueuedTeams.Add(BattlefieldName, TeamID);
        UE_LOG(LogTemp, Log, TEXT("Team %d queued for battle at %s"), TeamID, *BattlefieldName);
        FindOpponentForBattle(BattlefieldName);
    }
    else
    {
        int32 OpponentID = QueuedTeams[BattlefieldName];
        StartClanBattle(BattlefieldName, OpponentID, TeamID);
        QueuedTeams.Remove(BattlefieldName);
    }
}

// Uses an online matchmaking system to find an opponent
void AMultiplayerManager::FindOpponentForBattle(FString BattlefieldName)
{
    if (QueuedTeams.Contains(BattlefieldName))
    {
        int32 Team1ID = QueuedTeams[BattlefieldName];

        IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
        if (OnlineSubsystem)
        {
            IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
            if (SessionInterface.IsValid())
            {
                FOnlineSessionSearch SearchSettings;
                SearchSettings.bIsLanQuery = false;
                SearchSettings.MaxSearchResults = 10;
                SearchSettings.QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

                SessionInterface->FindSessions(0, SearchSettings);

                if (SearchSettings.SearchResults.Num() > 0)
                {
                    int32 OpponentID = SearchSettings.SearchResults[0].PingInMs; // Placeholder for real team ID
                    StartClanBattle(BattlefieldName, Team1ID, OpponentID);
                    QueuedTeams.Remove(BattlefieldName);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("No opponent found yet. Searching..."));
                }
            }
        }
    }
}

// Starts the clan battle once both teams are found
void AMultiplayerManager::StartClanBattle(FString BattlefieldName, int32 Team1ID, int32 Team2ID)
{
    UE_LOG(LogTemp, Log, TEXT("Starting Clan Battle: %s - Team %d vs Team %d"), *BattlefieldName, Team1ID, Team2ID);

    NotifyTeamsOfMatchStart(Team1ID, Team2ID, BattlefieldName);

    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            FOnlineSessionSettings SessionSettings;
            SessionSettings.bIsDedicated = false;
            SessionSettings.bUsesPresence = true;
            SessionSettings.NumPublicConnections = 12; // 6v6
            SessionSettings.bAllowJoinInProgress = false;

            SessionInterface->CreateSession(0, FName(*BattlefieldName), SessionSettings);
        }
    }

    // **Sync Weather for All Players**
    ServerSetWeatherForBattle(BattlefieldName);
}

// Ends the battle and updates ownership of the battlefield
void AMultiplayerManager::EndClanBattle(FString BattlefieldName, int32 WinningTeamID)
{
    UE_LOG(LogTemp, Log, TEXT("Battle at %s ended. Winning team: %d"), *BattlefieldName, WinningTeamID);
    UpdateBattlefieldOwnership(BattlefieldName, WinningTeamID);
}

// Updates the battlefield ownership after a match
void AMultiplayerManager::UpdateBattlefieldOwnership(FString BattlefieldName, int32 NewOwnerTeam)
{
    AMapManager* MapManager = Cast<AMapManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMapManager::StaticClass()));

    if (MapManager)
    {
        MapManager->UpdateControlPointOwnership(BattlefieldName, NewOwnerTeam);
    }
}

// Notifies both teams that the match has started using UI
void AMultiplayerManager::NotifyTeamsOfMatchStart(int32 Team1ID, int32 Team2ID, FString BattlefieldName)
{
    AHUDManager* HUDManager = Cast<AHUDManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AHUDManager::StaticClass()));

    if (HUDManager)
    {
        FString NotificationMessage = FString::Printf(TEXT("Battle at %s - Team %d vs Team %d has started!"), *BattlefieldName, Team1ID, Team2ID);
        HUDManager->DisplayMatchNotification(NotificationMessage);
    }

    UE_LOG(LogTemp, Log, TEXT("Teams %d and %d have been assigned to battle at %s!"), Team1ID, Team2ID, *BattlefieldName);
}

// **NETWORKED WEATHER SYNC**
void AMultiplayerManager::ServerSetWeatherForBattle(FString BattlefieldName)
{
    ADynamicWeather* WeatherManager = Cast<ADynamicWeather>(UGameplayStatics::GetActorOfClass(GetWorld(), ADynamicWeather::StaticClass()));

    if (WeatherManager)
    {
        EWeatherCondition ChosenWeather = WeatherManager->DetermineWeatherForRegion(BattlefieldName);
        WeatherManager->SetGlobalWeather(ChosenWeather);

        UE_LOG(LogTemp, Log, TEXT("Weather for %s set to %s"), *BattlefieldName, *UEnum::GetValueAsString(ChosenWeather));

        // Apply the chosen weather effects to all players
        ApplyWeatherEffectsToAllPlayers(ChosenWeather);
    }
}

// **APPLIES WEATHER EFFECTS TO ALL PLAYERS IN MATCH**
void AMultiplayerManager::ApplyWeatherEffectsToAllPlayers(EWeatherCondition ChosenWeather)
{
    for (TActorIterator<ACharacter> PlayerIterator(GetWorld()); PlayerIterator; ++PlayerIterator)
    {
        ACharacter* PlayerMech = *PlayerIterator;
        if (PlayerMech)
        {
            ADynamicWeather* WeatherManager = Cast<ADynamicWeather>(UGameplayStatics::GetActorOfClass(GetWorld(), ADynamicWeather::StaticClass()));
            if (WeatherManager)
            {
                WeatherManager->ApplyWeatherEffectsToMech(PlayerMech);
            }
        }
    }
}

// **SYNC ENEMY DETECTIONS ACROSS ONLINE MATCHES**
void AMultiplayerManager::SyncEnemyDetection(ACharacter* DetectedEnemy)
{
    if (!DetectedEnemy) return;

    FVector EnemyLocation = DetectedEnemy->GetActorLocation();

    // Broadcast to all players
    for (TActorIterator<APlayerController> PlayerIterator(GetWorld()); PlayerIterator; ++PlayerIterator)
    {
        APlayerController* PlayerController = *PlayerIterator;
        if (PlayerController)
        {
            UMinimapWidget* Minimap = Cast<UMinimapWidget>(PlayerController->GetHUD()->GetUserWidgetObject());
            if (Minimap)
            {
                Minimap->AddEnemyToMinimap(EnemyLocation);
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Enemy detected at %s and synced across all clients"), *EnemyLocation.ToString());
}