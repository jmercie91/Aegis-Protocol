#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.h" // Assuming you have a base Weapon class (e.g., AssaultRifle, SniperRifle, etc.)
#include "LoadoutManager.generated.h"

// Forward declarations for the mech parts and blueprint
USTRUCT(BlueprintType)
struct FMechBlueprint
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Mech Stats")
    FString BlueprintName;

    UPROPERTY(BlueprintReadWrite, Category = "Mech Components")
    ECockpitSize CockpitSize;

    UPROPERTY(BlueprintReadWrite, Category = "Mech Components")
    FCockpitModifiers CockpitModifiers;

    UPROPERTY(BlueprintReadWrite, Category = "Mech Components")
    TArray<FString> Weapons; // List of weapons

    UPROPERTY(BlueprintReadWrite, Category = "Mech Stats")
    float Health;

    UPROPERTY(BlueprintReadWrite, Category = "Mech Stats")
    float Speed;

    UPROPERTY(BlueprintReadWrite, Category = "Mech Stats")
    float Armor;

    UPROPERTY(BlueprintReadWrite, Category = "Mech Stats")
    float Energy;

    UPROPERTY(BlueprintReadWrite, Category = "Mech Components")
    TArray<FString> Parts; // List of other parts like armor, legs, etc.
};

UCLASS()
class AEGISPROTOCOL_API ALoadoutManager : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ALoadoutManager();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to load the saved blueprint from SaveGame or file
    UFUNCTION(BlueprintCallable, Category = "Loadout")
    FMechBlueprint LoadBlueprint();

    // Function to apply the loaded blueprint to the player's mech
    UFUNCTION(BlueprintCallable, Category = "Loadout")
    void ApplyBlueprintToMech(const FMechBlueprint& Blueprint);

private:
    // Function to equip weapons for the player's mech
    void EquipWeapon(const FString& WeaponName);

    // Function to update the mech's stats
    void UpdateMechStats(const FMechBlueprint& Blueprint);
};