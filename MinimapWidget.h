// Aegis Protocol - MinimapWidget.h
// Manages the minimap UI, displaying detected enemies and teammates.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

UCLASS()
class AEGISPROTOCOL_API UMinimapWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Adds an enemy to the minimap
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void AddEnemyToMinimap(FVector EnemyLocation);

    // Removes an enemy from the minimap
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void RemoveEnemyFromMinimap(FVector EnemyLocation);

    // Updates teammate positions on the minimap
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void UpdateTeammatePositions(const TArray<FVector>& TeammateLocations);

protected:
    virtual void NativeConstruct() override;

private:
    // Stores enemy locations for rendering on the minimap
    UPROPERTY()
    TArray<FVector> EnemyPositions;

    // Stores teammate locations
    UPROPERTY()
    TArray<FVector> TeammatePositions;

    // Refreshes the minimap display
    void RefreshMinimap();
};