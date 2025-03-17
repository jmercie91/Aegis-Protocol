// Aegis Protocol - WeatherSystem.h
// Manages real-time dynamic weather, syncs across multiplayer, and affects radar & mech performance.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "WeatherSystem.generated.h"

// Enum defining different weather conditions
UENUM(BlueprintType)
enum class EWeatherCondition : uint8
{
    Clear UMETA(DisplayName = "Clear"),
    Rain UMETA(DisplayName = "Rain"),
    Storm UMETA(DisplayName = "Storm"),
    Snow UMETA(DisplayName = "Snow"),
    Sandstorm UMETA(DisplayName = "Sandstorm"),
    Fog UMETA(DisplayName = "Fog")
};

// Enum defining regional weather influences
UENUM(BlueprintType)
enum class EWeatherRegion : uint8
{
    UnitedFront UMETA(DisplayName = "United Front"),  // USA - Mostly clear, some rain/storms
    ZephyrDominion UMETA(DisplayName = "Zephyr Dominion"), // Middle East - Clear & sandstorms
    VolkovImperium UMETA(DisplayName = "Volkov Imperium"), // Russia - Frequent snow & storms
    PhantomSyndicate UMETA(DisplayName = "Phantom Syndicate") // Jungle - Rain & fog
};

UCLASS()
class AEGISPROTOCOL_API AWeatherSystem : public AActor
{
    GENERATED_BODY()

public:
    AWeatherSystem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Function to set the weather based on region
    UFUNCTION(BlueprintCallable, Category = "Weather")
    void SetWeather(EWeatherRegion Region);

    // Function to manually trigger a weather change
    UFUNCTION(BlueprintCallable, Category = "Weather")
    void ChangeWeather();

    // Function to apply weather effects to a specific mech
    void ApplyWeatherEffectsToMech(ACharacter* Mech);

    // Function to remove weather effects from a mech when conditions change
    void RemoveWeatherEffectsFromMech(ACharacter* Mech);

    // Multiplayer function to sync weather across all players
    UFUNCTION(NetMulticast, Reliable)
    void SyncWeatherForAllPlayers(EWeatherCondition NewWeather);

    // Function to adjust radar visibility based on weather
    void AdjustRadarVisibility();

private:
    // Current weather state
    EWeatherCondition CurrentWeather;

    // Current regional weather settings
    EWeatherRegion CurrentRegion;

    // Particle effects for different weather types
    UPROPERTY(EditAnywhere, Category = "Weather Effects")
    UParticleSystem* RainEffect;

    UPROPERTY(EditAnywhere, Category = "Weather Effects")
    UParticleSystem* StormEffect;

    UPROPERTY(EditAnywhere, Category = "Weather Effects")
    UParticleSystem* SnowEffect;

    UPROPERTY(EditAnywhere, Category = "Weather Effects")
    UParticleSystem* SandstormEffect;

    UPROPERTY(EditAnywhere, Category = "Weather Effects")
    UParticleSystem* FogEffect;

    // Audio cues for weather conditions
    UPROPERTY(EditAnywhere, Category = "Weather Sounds")
    USoundCue* RainSound;

    UPROPERTY(EditAnywhere, Category = "Weather Sounds")
    USoundCue* StormSound;

    UPROPERTY(EditAnywhere, Category = "Weather Sounds")
    USoundCue* SnowSound;

    UPROPERTY(EditAnywhere, Category = "Weather Sounds")
    USoundCue* SandstormSound;

    UPROPERTY(EditAnywhere, Category = "Weather Sounds")
    USoundCue* FogSound;

    // Active weather effect
    UPROPERTY()
    UParticleSystemComponent* ActiveWeatherEffect;

    // Timer handle for periodic weather changes
    FTimerHandle WeatherTimerHandle;

    // Function to play the appropriate weather effects
    void PlayWeatherEffects();

    // Function to stop any active weather effects
    void StopWeatherEffects();
};
