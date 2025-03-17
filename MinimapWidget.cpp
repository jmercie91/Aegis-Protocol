// Aegis Protocol - MinimapWidget.cpp
// Implements the logic for tracking enemies and teammates on the minimap.

#include "MinimapWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"

void UMinimapWidget::NativeConstruct()
{
    Super::NativeConstruct();
    RefreshMinimap();
}

void UMinimapWidget::AddEnemyToMinimap(FVector EnemyLocation)
{
    if (!EnemyPositions.Contains(EnemyLocation))
    {
        EnemyPositions.Add(EnemyLocation);
        RefreshMinimap();
        UE_LOG(LogTemp, Log, TEXT("Enemy added to minimap at location: %s"), *EnemyLocation.ToString());
    }
}

void UMinimapWidget::RemoveEnemyFromMinimap(FVector EnemyLocation)
{
    if (EnemyPositions.Contains(EnemyLocation))
    {
        EnemyPositions.Remove(EnemyLocation);
        RefreshMinimap();
        UE_LOG(LogTemp, Log, TEXT("Enemy removed from minimap at location: %s"), *EnemyLocation.ToString());
    }
}

void UMinimapWidget::UpdateTeammatePositions(const TArray<FVector>& TeammateLocations)
{
    TeammatePositions = TeammateLocations;
    RefreshMinimap();
}

void UMinimapWidget::RefreshMinimap()
{
    // Logic to visually update the minimap UI with enemy and teammate positions.
    UE_LOG(LogTemp, Log, TEXT("Minimap refreshed with %d enemies and %d teammates."), EnemyPositions.Num(), TeammatePositions.Num());
}