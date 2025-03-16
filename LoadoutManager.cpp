#include "LoadoutManager.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MechCharacter.h" // Assuming this is your mech character class

// Sets default values
ALoadoutManager::ALoadoutManager()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALoadoutManager::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ALoadoutManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to load the saved blueprint from SaveGame or file
FMechBlueprint ALoadoutManager::LoadBlueprint()
{
    FMechBlueprint LoadedBlueprint;

    // Load the saved blueprint from the SaveGame system
    UGameplayStatics::LoadGameFromSlot("MechBlueprint", 0);

    // If the loaded game data is valid, return the loaded blueprint
    if (LoadedGame)
    {
        LoadedBlueprint = LoadedGame->SavedBlueprint;
    }

    return LoadedBlueprint;
}

// Function to apply the loaded blueprint to the player's mech
void ALoadoutManager::ApplyBlueprintToMech(const FMechBlueprint& Blueprint)
{
    // Assuming AMechCharacter is the player class
    AMechCharacter* PlayerMech = Cast<AMechCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (PlayerMech)
    {
        // Apply the selected blueprint to the player's mech
        PlayerMech->SetCockpitSize(Blueprint.CockpitSize);
        PlayerMech->SetHealth(Blueprint.Health);
        PlayerMech->SetSpeed(Blueprint.Speed);
        PlayerMech->SetArmor(Blueprint.Armor);
        PlayerMech->SetEnergy(Blueprint.Energy);

        // Equip the weapons
        for (const FString& WeaponName : Blueprint.Weapons)
        {
            EquipWeapon(WeaponName);
        }

        // Update any other part of the mech stats
        UpdateMechStats(Blueprint);
    }
}

// Function to equip weapons for the player's mech
void ALoadoutManager::EquipWeapon(const FString& WeaponName)
{
    // Logic to equip the weapon based on the name or loadout
    UE_LOG(LogTemp, Log, TEXT("Equipped weapon: %s"), *WeaponName);

    // Assuming WeaponName corresponds to the class of the weapon you want to equip.
    // For example, we could have different weapon classes for different types: sniper, assault rifle, etc.

    TSubclassOf<AWeapon> WeaponClass = nullptr;

    // Find the weapon class based on the WeaponName
    if (WeaponName == "AssaultRifle")
    {
        WeaponClass = AAssaultRifle::StaticClass();
    }
    else if (WeaponName == "SniperRifle")
    {
        WeaponClass = ASniperRifle::StaticClass();
    }
    else if (WeaponName == "RocketLauncher")
    {
        WeaponClass = ARocketLauncher::StaticClass();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon %s not found!"), *WeaponName);
        return;
    }

    // If we have a valid WeaponClass, spawn the weapon
    if (WeaponClass != nullptr)
    {
        // Get the player's mech character (this assumes your mech is an actor or character)
        AMechCharacter* PlayerMech = Cast<AMechCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

        if (PlayerMech)
        {
            // Spawn the weapon in the game world
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = PlayerMech; // Set the owner to the player's mech
            AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, PlayerMech->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

            if (NewWeapon)
            {
                // Attach the weapon to a specific socket on the mech (e.g., hand, back, etc.)
                USkeletalMeshComponent* MechMesh = PlayerMech->GetMesh();
                if (MechMesh)
                {
                    // Example of attaching to a specific socket (adjust the socket name as needed)
                    MechMesh->AttachActorToComponent(NewWeapon, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("WeaponSocket"));
                }

                // Optionally, you can set additional parameters (e.g., ammo, fire rate, etc.) for the weapon
                NewWeapon->SetOwner(PlayerMech);
                UE_LOG(LogTemp, Log, TEXT("Weapon %s equipped!"), *WeaponName);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to spawn weapon %s!"), *WeaponName);
            }
        }
    }
}

// Function to update the mech's stats (like health, speed, etc.)
void ALoadoutManager::UpdateMechStats(const FMechBlueprint& Blueprint)
{
    // Example of how stats might be applied
    if (Blueprint.Health > 0)
    {
        // Update the health or other stats accordingly
        UE_LOG(LogTemp, Log, TEXT("Mech health updated to: %f"), Blueprint.Health);
    }

    if (Blueprint.Speed > 0)
    {
        // Update speed or other stats accordingly
        UE_LOG(LogTemp, Log, TEXT("Mech speed updated to: %f"), Blueprint.Speed);
    }
}