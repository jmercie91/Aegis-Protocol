// // Aegis Protocol - HUDManager.h
// Manages world map UI, battlefield selection, minimap interactions, and enemy detection.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDManager.generated.h"

UENUM(BlueprintType)
enum class EFactionType : uint8
{
    UnitedFront UMETA(DisplayName = "United Front"),   // USA-Inspired
    ZephyrDominion UMETA(DisplayName = "Zephyr Dominion"), // Middle East-Inspired
    VolkovImperium UMETA(DisplayName = "Volkov Imperium"), // Russia-Inspired
    PhantomSyndicate UMETA(DisplayName = "Phantom Syndicate") // South Pacific-Inspired
};

USTRUCT(BlueprintType)
struct FBattlefieldInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield Info")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield Info")
    EFactionType Faction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield Info")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield Info")
    int32 ControllingTeam;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battlefield Info")
    bool bIsCapital;
};

UCLASS()
class AEGISPROTOCOL_API AHUDManager : public AHUD
{
    GENERATED_BODY()

public:
    AHUDManager();

    virtual void BeginPlay() override;
    virtual void DrawHUD() override;

    // 🌍 **World Map & Battlefields**
    void DisplayWorldMap();
    void DisplayBattlefieldInfo(FString SelectedBattlefield);
    void SelectBattlefield(FString BattlefieldName);

    // 🔥 **NEW: Minimap Enemy Detection**
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void DisplayEnemyOnMinimap(FVector EnemyLocation);

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void ClearEnemyMarkers();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    TArray<FBattlefieldInfo> Battlefields;

private:
    void InitializeBattlefields();
    void QueueForBattle(FString BattlefieldName);

    // Reference to the Minimap UI Widget
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
    class UMinimapWidget* MinimapWidget;
};