// Aegis Protocol - WeaponSystem.cpp
// Implements core weapon mechanics, firing, reloading, and ammo system

#include "WeaponSystem.h"
#include "WeaponSlotSystem.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AWeaponSystem::AWeaponSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    TotalWeight = 0.0f;
    WeaponSlotSystem = CreateDefaultSubobject<AWeaponSlotSystem>(TEXT("WeaponSlotSystem"));
}

void AWeaponSystem::BeginPlay()
{
    Super::BeginPlay();
}

void AWeaponSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeaponSystem::FireWeapon()
{
    if (CanFire())
    {
        // Get equipped weapon
        FWeaponStats* ActiveWeapon = EquippedWeapons.Find(EWeaponSlot::Right); // Default to right-side weapon
        if (!ActiveWeapon) return;

        UE_LOG(LogTemp, Log, TEXT("Weapon fired: %s"), *UEnum::GetValueAsString(ActiveWeapon->WeaponType));

        FVector MuzzleLocation = GetActorLocation();
        FRotator MuzzleRotation = GetActorRotation();
        FHitResult HitResult;

        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);

        FVector Start = MuzzleLocation;
        FVector End = Start + (MuzzleRotation.Vector() * ActiveWeapon->Range);

        if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
        {
            ApplyWeaponEffects(HitResult.GetActor());
        }
    }
}

void AWeaponSystem::ApplyWeaponEffects(AActor* HitTarget)
{
    if (HitTarget)
    {
        UE_LOG(LogTemp, Log, TEXT("Hit Target: %s"), *HitTarget->GetName());
    }
}

bool AWeaponSystem::CanFire() const
{
    return true; // No ammo restrictions for now
}

void AWeaponSystem::ReloadWeapon()
{
    UE_LOG(LogTemp, Log, TEXT("Reloading..."));
}

void AWeaponSystem::AttachWeapon(EWeaponSlot Slot, FWeaponStats Weapon)
{
    EquippedWeapons.Add(Slot, Weapon);
    TotalWeight += Weapon.Weight;
    UE_LOG(LogTemp, Log, TEXT("Attached weapon: %s to slot %s"), *UEnum::GetValueAsString(Weapon.WeaponType), *UEnum::GetValueAsString(Slot));
}

float AWeaponSystem::GetWeaponWeight()
{
    return TotalWeight;
}

void AWeaponSystem::SwitchWeapon(EWeaponType NewWeaponType)
{
    for (auto& Weapon : EquippedWeapons)
    {
        if (Weapon.Value.WeaponType == NewWeaponType)
        {
            UE_LOG(LogTemp, Log, TEXT("Switched to weapon: %s"), *UEnum::GetValueAsString(NewWeaponType));
            return;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Weapon %s not found in loadout!"), *UEnum::GetValueAsString(NewWeaponType));
}

EWeaponType AWeaponSystem::GetCurrentWeaponType() const
{
    if (EquippedWeapons.Contains(EWeaponSlot::Right))
    {
        return EquippedWeapons[EWeaponSlot::Right].WeaponType;
    }
    return EWeaponType::AssaultRifle;
}