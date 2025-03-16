// Aegis Protocol - BeaconTower.cpp
// Implements beacon capture mechanics, recapture logic, and radar visibility

#include "BeaconTower.h"
#include "MechCharacter.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ABeaconTower::ABeaconTower()
{
    PrimaryActorTick.bCanEverTick = true;
    OwningTeam = 0;
    CaptureTimeRequired = 10.0f;
    CurrentCaptureTime = 0.0f;
    CaptureRadius = 1000.0f; // 10 meters in Unreal units
    CapturingMech = nullptr;
}

void ABeaconTower::BeginPlay()
{
    Super::BeginPlay();
}

void ABeaconTower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CapturingMech)
    {
        if (!IsWithinCaptureRadius(CapturingMech))
        {
            ResetCapture();
            return;
        }

        CurrentCaptureTime += DeltaTime;

        if (CurrentCaptureTime >= CaptureTimeRequired)
        {
            CompleteCapture();
        }
    }
}

void ABeaconTower::BeginCapture(AMechCharacter* CapturingMech)
{
    if (CapturingMech)
    {
        if (CapturingMech->GetTeamID() == OwningTeam)
        {
            return; // No need to capture if it's already owned by the team
        }

        if (this->CapturingMech != CapturingMech)
        {
            this->CapturingMech = CapturingMech;
            CurrentCaptureTime = 0.0f;
        }
    }
}

void ABeaconTower::ContinueCapture(AMechCharacter* CapturingMech)
{
    if (CapturingMech && CapturingMech == this->CapturingMech)
    {
        if (!IsWithinCaptureRadius(CapturingMech))
        {
            ResetCapture();
        }
    }
}

void ABeaconTower::CompleteCapture()
{
    if (CapturingMech)
    {
        OwningTeam = CapturingMech->GetTeamID();
        CurrentCaptureTime = 0.0f;
        CapturingMech = nullptr;
    }
}

void ABeaconTower::ResetCapture()
{
    CurrentCaptureTime = 0.0f;
    CapturingMech = nullptr;
}

void ABeaconTower::RevealMechOnRadar(AMechCharacter* Mech)
{
    if (Mech && !Mech->bIsRadarDisabled)
    {
        Mech->bIsVisibleOnRadar = true;
        UE_LOG(LogTemp, Log, TEXT("Mech at %s is now visible on radar!"), *Mech->GetActorLocation().ToString());
    }
}

bool ABeaconTower::IsWithinCaptureRadius(AMechCharacter* Mech) const
{
    if (!Mech) return false;

    float Distance = FVector::Dist(Mech->GetActorLocation(), GetActorLocation());
    return Distance <= CaptureRadius;
}

int32 ABeaconTower::GetOwningTeam() const
{
    return OwningTeam;
}