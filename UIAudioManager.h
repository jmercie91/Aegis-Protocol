// Aegis Protocol - UIAudioManager.h
// Manages UI sounds including button clicks, menu transitions, and notifications.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "UIAudioManager.generated.h"

UCLASS()
class AEGISPROTOCOL_API AUIAudioManager : public AActor
{
    GENERATED_BODY()

public:
    AUIAudioManager();

protected:
    virtual void BeginPlay() override;

public:
    // Play sound for button clicks
    UFUNCTION(BlueprintCallable, Category = "UI Audio")
    void PlayButtonClickSound();

    // Play sound for menu opening/closing transitions
    UFUNCTION(BlueprintCallable, Category = "UI Audio")
    void PlayMenuTransitionSound();

    // Play sound for system notifications (error, success, warning)
    UFUNCTION(BlueprintCallable, Category = "UI Audio")
    void PlayNotificationSound(EMessageType MessageType);

    // Play sound for in-game alerts (e.g., radar warnings, damage alerts)
    UFUNCTION(BlueprintCallable, Category = "UI Audio")
    void PlayInGameAlertSound(EAlertType AlertType);

private:
    // UI button click sound
    UPROPERTY(EditAnywhere, Category = "UI Audio")
    USoundCue* ButtonClickSound;

    // UI menu transition sound
    UPROPERTY(EditAnywhere, Category = "UI Audio")
    USoundCue* MenuTransitionSound;

    // Notification sounds
    UPROPERTY(EditAnywhere, Category = "UI Audio")
    USoundCue* SuccessNotificationSound;

    UPROPERTY(EditAnywhere, Category = "UI Audio")
    USoundCue* ErrorNotificationSound;

    UPROPERTY(EditAnywhere, Category = "UI Audio")
    USoundCue* WarningNotificationSound;

    // Alert sounds
    UPROPERTY(EditAnywhere, Category = "UI Audio")
    USoundCue* RadarAlertSound;

    UPROPERTY(EditAnywhere, Category = "UI Audio")
    USoundCue* DamageAlertSound;

    UPROPERTY(EditAnywhere, Category = "UI Audio")
    USoundCue* ObjectiveAlertSound;
};

// Enum for different notification types
UENUM(BlueprintType)
enum class EMessageType : uint8
{
    Success UMETA(DisplayName = "Success"),
    Error UMETA(DisplayName = "Error"),
    Warning UMETA(DisplayName = "Warning")
};

// Enum for in-game alert types
UENUM(BlueprintType)
enum class EAlertType : uint8
{
    RadarWarning UMETA(DisplayName = "Radar Warning"),
    DamageWarning UMETA(DisplayName = "Damage Warning"),
    ObjectiveUpdate UMETA(DisplayName = "Objective Update")
};