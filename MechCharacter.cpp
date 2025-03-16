#include "MechCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AMechCharacter::AMechCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default Mech Stats
    MaxHealth = 2000.0f;
    Health = MaxHealth;
    Speed = 600.0f;
    TurnRate = 70.0f;
    MaxWeight = 150.0f;

    bIsRadarDisabled = false;
    bIsHUDDisabled = false;
}

void AMechCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMechCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMechCharacter::SetMechLegs(ELegType SelectedLegType)
{
    if (LegConfiguration)
    {
        LegConfiguration->SetLegType(SelectedLegType);
        Speed = LegConfiguration->GetSpeedModifier() * 600.0f;
        TurnRate = LegConfiguration->GetTurnSpeed();
        MaxWeight = LegConfiguration->GetWeightCapacity();

        UE_LOG(LogTemp, Log, TEXT("Mech Legs Updated: %d | Speed: %.2f | TurnRate: %.2f | Weight: %.2f"),
            static_cast<int32>(SelectedLegType), Speed, TurnRate, MaxWeight);
    }
}

void AMechCharacter::TakeDamage(float DamageAmount)
{
    Health -= DamageAmount;
    UE_LOG(LogTemp, Log, TEXT("Mech took damage: %.1f | Health Remaining: %.1f"), DamageAmount, Health);

    if (Health <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Mech Destroyed!"));
        Destroy();
    }
}

void AMechCharacter::AttachWeapon(AActor* NewWeapon)
{
    if (NewWeapon)
    {
        EquippedWeapon = NewWeapon;
        UE_LOG(LogTemp, Log, TEXT("Weapon Attached: %s"), *NewWeapon->GetName());
    }
}

void AMechCharacter::DetachWeapon()
{
    if (EquippedWeapon)
    {
        UE_LOG(LogTemp, Log, TEXT("Weapon Detached: %s"), *EquippedWeapon->GetName());
        EquippedWeapon = nullptr;
    }
}

void AMechCharacter::DisableRadar(float DisableDuration)
{
    if (!bIsRadarDisabled)
    {
        bIsRadarDisabled = true;
        UE_LOG(LogTemp, Log, TEXT("Radar Disabled!"));

        GetWorldTimerManager().SetTimer(
            FTimerHandle(), this, &AMechCharacter::RestoreRadar, DisableDuration, false);
    }
}

void AMechCharacter::RestoreRadar()
{
    bIsRadarDisabled = false;
    UE_LOG(LogTemp, Log, TEXT("Radar Restored!"));
}

void AMechCharacter::DisableHUD(float DisableDuration)
{
    if (!bIsHUDDisabled)
    {
        bIsHUDDisabled = true;
        UE_LOG(LogTemp, Log, TEXT("HUD Disabled!"));

        GetWorldTimerManager().SetTimer(
            FTimerHandle(), this, &AMechCharacter::RestoreHUD, DisableDuration, false);
    }
}

void AMechCharacter::RestoreHUD()
{
    bIsHUDDisabled = false;
    UE_LOG(LogTemp, Log, TEXT("HUD Restored!"));
}