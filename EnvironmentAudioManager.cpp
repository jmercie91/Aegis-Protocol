// Aegis Protocol - EnvironmentAudioManager.cpp
// Implements dynamic environmental and weather-based audio effects.

#include "EnvironmentAudioManager.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

AEnvironmentAudioManager::AEnvironmentAudioManager()
{
    PrimaryActorTick.bCanEverTick = false;

    // Initialize audio components for environments
    UrbanAmbienceComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("UrbanAmbience"));
    DesertAmbienceComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DesertAmbience"));
    JungleAmbienceComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("JungleAmbience"));
    ArcticAmbienceComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ArcticAmbience"));
    BattlefieldAmbienceComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BattlefieldAmbience"));

    // Initialize weather audio components
    RainAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("RainAudio"));
    StormAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("StormAudio"));
    SnowAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SnowAudio"));
    SandstormAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SandstormAudio"));
    BattleAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BattleAudio"));

    // Disable auto activation at start
    UrbanAmbienceComponent->bAutoActivate = false;
    DesertAmbienceComponent->bAutoActivate = false;
    JungleAmbienceComponent->bAutoActivate = false;
    ArcticAmbienceComponent->bAutoActivate = false;
    BattlefieldAmbienceComponent->bAutoActivate = false;

    RainAudioComponent->bAutoActivate = false;
    StormAudioComponent->bAutoActivate = false;
    SnowAudioComponent->bAutoActivate = false;
    SandstormAudioComponent->bAutoActivate = false;
    BattleAudioComponent->bAutoActivate = false;
}

void AEnvironmentAudioManager::BeginPlay()
{
    Super::BeginPlay();
    UpdateEnvironmentAudio();
    UpdateWeatherAudio();
}

void AEnvironmentAudioManager::SetEnvironment(EEnvironmentType NewEnvironment)
{
    if (CurrentEnvironment != NewEnvironment)
    {
        CurrentEnvironment = NewEnvironment;
        UpdateEnvironmentAudio();
    }
}

void AEnvironmentAudioManager::SetWeather(EWeatherType NewWeather)
{
    if (CurrentWeather != NewWeather)
    {
        CurrentWeather = NewWeather;
        UpdateWeatherAudio();
    }
}

void AEnvironmentAudioManager::UpdateEnvironmentAudio()
{
    StopAllEnvironmentAudio();

    switch (CurrentEnvironment)
    {
    case EEnvironmentType::Urban:
        UrbanAmbienceComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Environment: Urban - Playing city ambiance."));
        break;
    case EEnvironmentType::Desert:
        DesertAmbienceComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Environment: Desert - Playing desert wind sounds."));
        break;
    case EEnvironmentType::Jungle:
        JungleAmbienceComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Environment: Jungle - Playing rainforest ambiance."));
        break;
    case EEnvironmentType::Arctic:
        ArcticAmbienceComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Environment: Arctic - Playing cold wind ambiance."));
        break;
    case EEnvironmentType::Battlefield:
        BattlefieldAmbienceComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Environment: Battlefield - Playing war zone ambiance."));
        break;
    }
}

void AEnvironmentAudioManager::UpdateWeatherAudio()
{
    StopAllEnvironmentAudio();

    switch (CurrentWeather)
    {
    case EWeatherType::Clear:
        UE_LOG(LogTemp, Log, TEXT("Weather: Clear - No ambient sounds playing."));
        break;
    case EWeatherType::Rain:
        RainAudioComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Weather: Rain - Playing rain ambient audio."));
        break;
    case EWeatherType::Storm:
        StormAudioComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Weather: Storm - Playing storm sounds."));
        break;
    case EWeatherType::Snow:
        SnowAudioComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Weather: Snow - Playing snowstorm sounds."));
        break;
    case EWeatherType::Sandstorm:
        SandstormAudioComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Weather: Sandstorm - Playing heavy wind and sand effects."));
        break;
    }
}

void AEnvironmentAudioManager::PlayBattleAudio()
{
    if (BattleAudioComponent && !BattleAudioComponent->IsPlaying())
    {
        BattleAudioComponent->Play();
        UE_LOG(LogTemp, Log, TEXT("Playing battle ambient sounds."));
    }
}

void AEnvironmentAudioManager::StopAllEnvironmentAudio()
{
    UrbanAmbienceComponent->Stop();
    DesertAmbienceComponent->Stop();
    JungleAmbienceComponent->Stop();
    ArcticAmbienceComponent->Stop();
    BattlefieldAmbienceComponent->Stop();

    RainAudioComponent->Stop();
    StormAudioComponent->Stop();
    SnowAudioComponent->Stop();
    SandstormAudioComponent->Stop();
    BattleAudioComponent->Stop();

    UE_LOG(LogTemp, Log, TEXT("All environmental audio stopped."));
}