// Aegis Protocol - LoadoutManager.cpp
// Implements mech customization, weapon, armor, and stat management.

#include "LoadoutManager.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MechCharacter.h"
#include "WeaponSystem.h"

ALoadoutManager::ALoadoutManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ALoadoutManager::BeginPlay()
{
    Super::BeginPlay();
}

void ALoadoutManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

FMechLoadout ALoadoutManager::LoadLoadout()
{
    FMechLoadout LoadedLoadout;

    UGameplayStatics::LoadGameFromSlot("MechLoadout", 0);

    if (LoadedGame)
    {
        LoadedLoadout = LoadedGame->SavedLoadout;
    }

    return LoadedLoadout;
}

void ALoadoutManager::ApplyLoadoutToMech(const FMechLoadout& Loadout)
{
    AMechCharacter* PlayerMech = Cast<AMechCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (PlayerMech)
    {
        // Apply stats
        PlayerMech->SetHealth(Loadout.Health);
        PlayerMech->SetSpeed(Loadout.Speed);
        PlayerMech->SetArmor(Loadout.ArmorValue);
        PlayerMech->SetEnergy(Loadout.Energy);

        // Equip Weapons
        for (auto& WeaponSlot : Loadout.Weapons)
        {
            EquipWeapon(WeaponSlot.Key, WeaponSlot.Value, Loadout.AmmoTypes[WeaponSlot.Key]);
        }

        // Apply Armor
        ApplyArmor(Loadout.ArmorType);

        // Update Mech Stats
        UpdateMechStats(Loadout);
    }
}

void ALoadoutManager::SaveLoadout(const FMechLoadout& Loadout)
{
    UGameplayStatics::SaveGameToSlot(Loadout, "MechLoadout", 0);
}

void ALoadoutManager::EquipWeapon(EWeaponSlot Slot, const FString& WeaponName, EAmmoType AmmoType)
{
    UE_LOG(LogTemp, Log, TEXT("Equipping %s in %s slot with %s ammo"), *WeaponName, *UEnum::GetValueAsString(Slot), *UEnum::GetValueAsString(AmmoType));

    TSubclassOf<AWeapon> WeaponClass = nullptr;

    if (WeaponName == "AssaultRifle") WeaponClass = AAssaultRifle::StaticClass();
    else if (WeaponName == "SniperRifle") WeaponClass = ASniperRifle::StaticClass();
    else if (WeaponName == "Shotgun") WeaponClass = AShotgun::StaticClass();
    else if (WeaponName == "MachineGun") WeaponClass = AMachineGun::StaticClass();
    else if (WeaponName == "RocketLauncher") WeaponClass = ARocketLauncher::StaticClass();
    else if (WeaponName == "GrenadeLauncher") WeaponClass = AGrenadeLauncher::StaticClass();
    else if (WeaponName == "LockOnMissile") WeaponClass = ALockOnMissile::StaticClass();
    else if (WeaponName == "MeleeWeapon") WeaponClass = AMeleeWeapon::StaticClass();
    else if (WeaponName == "EMPWeapon") WeaponClass = AEMPWeapon::StaticClass();
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon %s not found!"), *WeaponName);
        return;
    }

    if (WeaponClass)
    {
        AMechCharacter* PlayerMech = Cast<AMechCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

        if (PlayerMech)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = PlayerMech;
            AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, PlayerMech->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

            if (NewWeapon)
            {
                PlayerMech->GetWeaponSlotSystem()->AssignWeapon(Slot, NewWeapon);
                NewWeapon->SetAmmoType(AmmoType);
                NewWeapon->SetOwner(PlayerMech);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to spawn weapon %s!"), *WeaponName);
            }
        }
    }
}

void ALoadoutManager::ApplyArmor(EArmorType ArmorType)
{
    UE_LOG(LogTemp, Log, TEXT("Armor Applied: %s"), *UEnum::GetValueAsString(ArmorType));

    AMechCharacter* PlayerMech = Cast<AMechCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (PlayerMech)
    {
        PlayerMech->GetArmorSystem()->SetArmorType(ArmorType);
    }
}

void ALoadoutManager::UpdateMechStats(const FMechLoadout& Loadout)
{
    AMechCharacter* PlayerMech = Cast<AMechCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (!PlayerMech) return;

    float TotalWeight = 0.0f;

    for (auto& WeaponSlot : Loadout.Weapons)
    {
        if (WeaponSlot.Value.Contains("SniperRifle")) TotalWeight += 25.0f;
        else if (WeaponSlot.Value.Contains("AssaultRifle")) TotalWeight += 15.0f;
        else if (WeaponSlot.Value.Contains("Shotgun")) TotalWeight += 18.0f;
        else if (WeaponSlot.Value.Contains("MachineGun")) TotalWeight += 30.0f;
        else if (WeaponSlot.Value.Contains("RocketLauncher")) TotalWeight += 40.0f;
        else if (WeaponSlot.Value.Contains("GrenadeLauncher")) TotalWeight += 35.0f;
        else if (WeaponSlot.Value.Contains("LockOnMissile")) TotalWeight += 20.0f;
        else if (WeaponSlot.Value.Contains("MeleeWeapon")) TotalWeight += 10.0f;
        else if (WeaponSlot.Value.Contains("EMPWeapon")) TotalWeight += 12.0f;
    }

    float AdjustedSpeed = Loadout.Speed - (TotalWeight * 0.1f);
    AdjustedSpeed = FMath::Clamp(AdjustedSpeed, 50.0f, Loadout.Speed);
    PlayerMech->SetSpeed(AdjustedSpeed);
}