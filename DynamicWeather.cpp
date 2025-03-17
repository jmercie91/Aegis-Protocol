// Aegis Protocol - DynamicWeather.cpp
// Implements real-time dynamic weather effects based on region and conditions.

#include "DynamicWeather.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MultiplayerManager.h"

ADynamicWeather::ADynamicWeather()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentWeather = EWeatherCondition::Clear;
    ActiveWeatherEffect = nullptr;
}

void ADynamicWeather::BeginPlay()
{
    Super::BeginPlay();

    // Start random weather changes every 3-5 minutes
    GetWorld()->GetTimerManager().SetTimer(WeatherTimerHandle, this, &ADynamicWeather::ChangeWeather, FMath::RandRange(180.0f, 300.0f), true);
}

void ADynamicWeather::SetWeather(EWeatherRegion Region)
{
    CurrentRegion = Region;
    ChangeWeather();
}

void ADynamicWeather::ChangeWeather()
{
    StopWeatherEffects();

    float RandomChance = FMath::RandRange(0.0f, 1.0f);

    switch (CurrentRegion)
    {
    case EWeatherRegion::UnitedFront: // USA - Mostly clear, occasional rain or storm
        if (RandomChance < 0.1f) CurrentWeather = EWeatherCondition::Rain;
        else if (RandomChance < 0.05f) CurrentWeather = EWeatherCondition::Storm;
        else CurrentWeather = EWeatherCondition::Clear;
        break;

    case EWeatherRegion::ZephyrDominion: // Middle East - Mostly clear, rare storms, frequent sandstorms
        if (RandomChance < 0.2f) CurrentWeather = EWeatherCondition::Sandstorm;
        else CurrentWeather = EWeatherCondition::Clear;
        break;

    case EWeatherRegion::VolkovImperium: // Russia - Frequent snow and storms
        if (RandomChance < 0.4f) CurrentWeather = EWeatherCondition::Snow;
        else if (RandomChance < 0.2f) CurrentWeather = EWeatherCondition::Storm;
        else CurrentWeather = EWeatherCondition::Clear;
        break;

    case EWeatherRegion::PhantomSyndicate: // Jungle - Frequent rain and fog
        if (RandomChance < 0.3f) CurrentWeather = EWeatherCondition::Rain;
        else if (RandomChance < 0.2f) CurrentWeather = EWeatherCondition::Fog;
        else CurrentWeather = EWeatherCondition::Clear;
        break;
    }

    PlayWeatherEffects();
}

void ADynamicWeather::PlayWeatherEffects()
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

    // Apply weather-based effects to mechs
    for (TActorIterator<ACharacter> MechIterator(GetWorld()); MechIterator; ++MechIterator)
    {
        ApplyWeatherEffectsToMech(*MechIterator);
    }

    // **Sync Weather Impact on Radar & Enemy Detection**
    AMultiplayerManager* MultiplayerManager = Cast<AMultiplayerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMultiplayerManager::StaticClass()));
    if (MultiplayerManager)
    {
        switch (CurrentWeather)
        {
        case EWeatherCondition::Sandstorm:
            MultiplayerManager->AdjustRadarRange(-50.0f);
            MultiplayerManager->AdjustEnemyDetection(-40.0f);
            break;
        case EWeatherCondition::Fog:
            MultiplayerManager->AdjustRadarRange(-30.0f);
            MultiplayerManager->AdjustEnemyDetection(-25.0f);
            break;
        case EWeatherCondition::Storm:
            MultiplayerManager->AdjustRadarRange(-25.0f);
            MultiplayerManager->AdjustEnemyDetection(-20.0f);
            break;
        default:
            MultiplayerManager->AdjustRadarRange(0.0f);
            MultiplayerManager->AdjustEnemyDetection(0.0f);
            break;
        }
    }
}

void ADynamicWeather::StopWeatherEffects()
{
    if (ActiveWeatherEffect)
    {
        ActiveWeatherEffect->DestroyComponent();
        ActiveWeatherEffect = nullptr;
    }

    UGameplayStatics::StopAllSoundsAtLocation(GetWorld(), GetActorLocation());

    // Remove effects from mechs
    for (TActorIterator<ACharacter> MechIterator(GetWorld()); MechIterator; ++MechIterator)
    {
        RemoveWeatherEffectsFromMech(*MechIterator);
    }
}

void ADynamicWeather::ApplyWeatherEffectsToMech(ACharacter* Mech)
{
    if (!Mech) return;

    UCharacterMovementComponent* MovementComp = Mech->FindComponentByClass<UCharacterMovementComponent>();
    AWeaponSystem* WeaponSystem = Cast<AWeaponSystem>(Mech->FindComponentByClass<UWeaponSystem>());
    APlayerController* PlayerController = Cast<APlayerController>(Mech->GetController());
    AMultiplayerManager* MultiplayerManager = Cast<AMultiplayerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMultiplayerManager::StaticClass()));

    switch (CurrentWeather)
    {
    case EWeatherCondition::Snow:
        if (MovementComp)
        {
            MovementComp->MaxWalkSpeed *= 0.85f;
        }
        if (WeaponSystem)
        {
            WeaponSystem->ModifyWeaponAccuracy(-10.0f);
        }
        break;

    case EWeatherCondition::Rain:
        if (MovementComp)
        {
            MovementComp->MaxWalkSpeed *= 0.9f;
        }
        if (WeaponSystem)
        {
            WeaponSystem->ModifyWeaponAccuracy(-5.0f);
        }
        break;

    case EWeatherCondition::Sandstorm:
        if (MovementComp)
        {
            MovementComp->MaxWalkSpeed *= 0.75f;
        }
        if (WeaponSystem)
        {
            WeaponSystem->ModifyWeaponAccuracy(-15.0f);
        }
        if (MultiplayerManager)
        {
            MultiplayerManager->AdjustRadarRange(-40.0f);
            MultiplayerManager->AdjustEnemyDetection(-40.0f);
        }
        break;

    case EWeatherCondition::Fog:
        if (MultiplayerManager)
        {
            MultiplayerManager->AdjustRadarRange(-30.0f);
            MultiplayerManager->AdjustEnemyDetection(-25.0f);
        }
        break;

    case EWeatherCondition::Storm:
        if (WeaponSystem)
        {
            WeaponSystem->ModifyWeaponAccuracy(-20.0f);
        }
        if (MultiplayerManager)
        {
            MultiplayerManager->AdjustEnemyDetection(-20.0f);
        }
        break;

    default:
        break;
    }
}

void ADynamicWeather::RemoveWeatherEffectsFromMech(ACharacter* Mech)
{
    if (!Mech) return;

    UCharacterMovementComponent* MovementComp = Mech->FindComponentByClass<UCharacterMovementComponent>();
    AWeaponSystem* WeaponSystem = Cast<AWeaponSystem>(Mech->FindComponentByClass<UWeaponSystem>());
    AMultiplayerManager* MultiplayerManager = Cast<AMultiplayerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMultiplayerManager::StaticClass()));

    if (MovementComp)
    {
        MovementComp->MaxWalkSpeed /= 0.85f;
        MovementComp->MaxWalkSpeed /= 0.9f;
        MovementComp->MaxWalkSpeed /= 0.75f;
    }

    if (WeaponSystem)
    {
        WeaponSystem->ModifyWeaponAccuracy(10.0f);
        WeaponSystem->ModifyWeaponAccuracy(5.0f);
        WeaponSystem->ModifyWeaponAccuracy(15.0f);
        WeaponSystem->ModifyWeaponAccuracy(20.0f);
    }

    if (MultiplayerManager)
    {
        MultiplayerManager->AdjustRadarRange(30.0f);
        MultiplayerManager->AdjustEnemyDetection(0.0f);
    }
}