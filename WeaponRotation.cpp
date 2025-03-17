// Aegis Protocol - WeaponRotation.cpp
// Implements weapon rotation functionality.

#include "WeaponRotation.h"
#include "GameFramework/Actor.h"

AWeaponRotation::AWeaponRotation()
{
    PrimaryActorTick.bCanEverTick = true;
    RotationSpeed = 1.0f; // Default rotation speed
    WeaponRotation = FRotator::ZeroRotator;
}

void AWeaponRotation::BeginPlay()
{
    Super::BeginPlay();
}

void AWeaponRotation::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeaponRotation::RotateWeapon(float RotationAmount)
{
    WeaponRotation.Yaw += RotationAmount * RotationSpeed;
    SetActorRotation(WeaponRotation);

    UE_LOG(LogTemp, Log, TEXT("Weapon rotated to: %s"), *WeaponRotation.ToString());
}

void AWeaponRotation::ResetWeaponRotation()
{
    WeaponRotation = FRotator::ZeroRotator;
    SetActorRotation(WeaponRotation);

    UE_LOG(LogTemp, Log, TEXT("Weapon rotation reset."));
}

FRotator AWeaponRotation::GetCurrentRotation() const
{
    return WeaponRotation;
}

void AWeaponRotation::SetWeaponRotation(FRotator NewRotation)
{
    WeaponRotation = NewRotation;
    SetActorRotation(WeaponRotation);

    UE_LOG(LogTemp, Log, TEXT("Weapon rotation manually set to: %s"), *NewRotation.ToString());
}