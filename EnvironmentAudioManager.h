// Aegis Protocol - EnvironmentAudioManager.h
// Manages dynamic environmental audio based on weather, terrain, and battle conditions.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "EnvironmentAudioManager.generated.h"

UENUM(BlueprintType)
enum class EEnvironmentType : uint8
{
    Urban UMETA(DisplayName = "Urban"),
    Desert UMETA(DisplayName = "Desert"),
    Jungle UMETA(DisplayName = "Jungle"),
    Arctic UMETA(DisplayName = "Arctic"),
    Battlefield UMETA(DisplayName = "Battlefield")
};

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
    Clear UMETA(DisplayName = "Clear"),
    Rain UMETA(DisplayName = "Rain"),
    Storm UMETA(DisplayName = "Storm"),
    Snow UMETA(DisplayName = "Snow"),
    Sandstorm UMETA(DisplayName = "Sandstorm")
};

UCLASS()
class AEGISPROTOCOL_API AEnvironmentAudioManager : public AActor
{
    GENERATED_BODY()

public:
    AEnvironmentAudioManager();

    // Set environment type dynamically
    void SetEnvironment(EEnvironmentType NewEnvironment);

    // Set weather type dynamically
    void SetWeather(EWeatherType NewWeather);

    // Stops all active environment audio
    void StopAllEnvironmentAudio();

    // Plays battle ambiance if a large engagement is happening
    void PlayBattleAudio();

protected:
    virtual void BeginPlay() override;

private:
    // Current environment & weather state
    EEnvironmentType CurrentEnvironment;
    EWeatherType CurrentWeather;

    // Audio components for environments
    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* UrbanAmbienceComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* DesertAmbienceComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* JungleAmbienceComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* ArcticAmbienceComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* BattlefieldAmbienceComponent;

    // Audio components for weather effects
    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* RainAudioComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* StormAudioComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* SnowAudioComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* SandstormAudioComponent;

    UPROPERTY(EditAnywhere, Category = "Audio")
    UAudioComponent* BattleAudioComponent;

    // Updates audio based on current environment
    void UpdateEnvironmentAudio();

    // Plays the appropriate sound for the current weather
    void UpdateWeatherAudio();
};