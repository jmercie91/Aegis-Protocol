// Aegis Protocol - WeatherSystem.cpp
// Implements real-time weather effects, multiplayer synchronization, and radar adjustments.

#include "WeatherSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MultiplayerManager.h"
#include "RadarHUD.h"

AWeatherSystem::AWeatherSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentWeather = EWeatherCondition::Clear;
    ActiveWeatherEffect = nullptr;
}

void AWeatherSystem::BeginPlay()
{
    Super::BeginPlay();

    // Start random weather changes every 3-5 minutes
    GetWorld()->GetTimerManager().SetTimer(WeatherTimerHandle, this, &AWeatherSystem::ChangeWeather, FMath::RandRange(180.0f, 300.0f), true);
}

void AWeatherSystem::SetWeather(EWeatherRegion Region)
{
    CurrentRegion = Region;
    ChangeWeather();
}

void AWeatherSystem::ChangeWeather()
{
    StopWeatherEffects();

    float RandomChance = FMath::RandRange(0.0f, 1.0f);

    switch (CurrentRegion)
    {
    case EWeatherRegion::UnitedFront:
        if (RandomChance < 0.1f) CurrentWeather = EWeatherCondition::Rain;
        else if (RandomChance < 0.05f) CurrentWeather = EWeatherCondition::Storm;
        else CurrentWeather = EWeatherCondition::Clear;
        break;
    case EWeatherRegion::ZephyrDominion:
        if (RandomChance < 0.2f) CurrentWeather = EWeatherCondition::Sandstorm;
        else CurrentWeather = EWeatherCondition::Clear;
        break;
    case EWeatherRegion::VolkovImperium:
        if (RandomChance < 0.4f) CurrentWeather = EWeatherCondition::Snow;
        else if (RandomChance < 0.2f) CurrentWeather = EWeatherCondition::Storm;
        else CurrentWeather = EWeatherCondition::Clear;
        break;
    case EWeatherRegion::PhantomSyndicate:
        if (RandomChance < 0.3f) CurrentWeather = EWeatherCondition::Rain;
        else if (RandomChance < 0.2f) CurrentWeather = EWeatherCondition::Fog;
        else CurrentWeather = EWeatherCondition::Clear;
        break;
    }

    PlayWeatherEffects();
    SyncWeatherForAllPlayers(CurrentWeather);
    AdjustRadarVisibility();
}

void AWeatherSystem::PlayWeatherEffects()
{
    UParticleSystem* SelectedEffect = nullptr;
    USoundCue* SelectedSound = nullptr;

    switch (CurrentWeather)
    {
    case EWeatherCondition::Rain:
        SelectedEffect = RainEffect;
        SelectedSound = RainSound;
        break;
    case EWeatherCondition::Storm:
        SelectedEffect = StormEffect;
        SelectedSound = StormSound;
        break;
    case EWeatherCondition::Snow:
        SelectedEffect = SnowEffect;
        SelectedSound = SnowSound;
        break;
    case EWeatherCondition::Sandstorm:
        SelectedEffect = SandstormEffect;
        SelectedSound = SandstormSound;
        break;
    case EWeatherCondition::Fog:
        SelectedEffect = FogEffect;
        SelectedSound = FogSound;
        break;
    default:
        break;
    }

    if (SelectedEffect)
    {
        ActiveWeatherEffect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, GetActorLocation());
    }

    if (SelectedSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), SelectedSound, GetActorLocation());
    }
}

void AWeatherSystem::StopWeatherEffects()
{
    if (ActiveWeatherEffect)
    {
        ActiveWeatherEffect->DestroyComponent();
        ActiveWeatherEffect = nullptr;
    }

    UGameplayStatics::StopAllSoundsAtLocation(GetWorld(), GetActorLocation());
}

void AWeatherSystem::SyncWeatherForAllPlayers(EWeatherCondition NewWeather)
{
    CurrentWeather = NewWeather;
    PlayWeatherEffects();
    AdjustRadarVisibility();
}

void AWeatherSystem::AdjustRadarVisibility()
{
    ARadarHUD* RadarHUD = Cast<ARadarHUD>(UGameplayStatics::GetActorOfClass(GetWorld(), ARadarHUD::StaticClass()));

    if (RadarHUD)
    {
        switch (CurrentWeather)
        {
        case EWeatherCondition::Fog:
        case EWeatherCondition::Storm:
        case EWeatherCondition::Sandstorm:
            RadarHUD->ReduceRadarRange(30.0f);
            break;
        default:
            RadarHUD->ResetRadarRange();
            break;
        }
    }
}