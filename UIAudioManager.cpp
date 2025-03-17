// Aegis Protocol - UIAudioManager.cpp
// Implements UI sounds including button clicks, menu transitions, and notifications.

#include "UIAudioManager.h"
#include "Kismet/GameplayStatics.h"

AUIAudioManager::AUIAudioManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AUIAudioManager::BeginPlay()
{
    Super::BeginPlay();
}

// Play button click sound
void AUIAudioManager::PlayButtonClickSound()
{
    if (ButtonClickSound)
    {
        UGameplayStatics::PlaySound2D(this, ButtonClickSound);
    }
}

// Play menu transition sound
void AUIAudioManager::PlayMenuTransitionSound()
{
    if (MenuTransitionSound)
    {
        UGameplayStatics::PlaySound2D(this, MenuTransitionSound);
    }
}

// Play notification sound based on message type
void AUIAudioManager::PlayNotificationSound(EMessageType MessageType)
{
    USoundCue* SelectedSound = nullptr;

    switch (MessageType)
    {
    case EMessageType::Success:
        SelectedSound = SuccessNotificationSound;
        break;
    case EMessageType::Error:
        SelectedSound = ErrorNotificationSound;
        break;
    case EMessageType::Warning:
        SelectedSound = WarningNotificationSound;
        break;
    default:
        break;
    }

    if (SelectedSound)
    {
        UGameplayStatics::PlaySound2D(this, SelectedSound);
    }
}

// Play in-game alert sound based on alert type
void AUIAudioManager::PlayInGameAlertSound(EAlertType AlertType)
{
    USoundCue* SelectedSound = nullptr;

    switch (AlertType)
    {
    case EAlertType::RadarWarning:
        SelectedSound = RadarAlertSound;
        break;
    case EAlertType::DamageWarning:
        SelectedSound = DamageAlertSound;
        break;
    case EAlertType::ObjectiveUpdate:
        SelectedSound = ObjectiveAlertSound;
        break;
    default:
        break;
    }

    if (SelectedSound)
    {
        UGameplayStatics::PlaySound2D(this, SelectedSound);
    }
}// Aegis Protocol - UIAudioManager.cpp
// Implements UI sounds including button clicks, menu transitions, and notifications.

#include "UIAudioManager.h"
#include "Kismet/GameplayStatics.h"

AUIAudioManager::AUIAudioManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AUIAudioManager::BeginPlay()
{
    Super::BeginPlay();
}

// Play button click sound
void AUIAudioManager::PlayButtonClickSound()
{
    if (ButtonClickSound)
    {
        UGameplayStatics::PlaySound2D(this, ButtonClickSound);
    }
}

// Play menu transition sound
void AUIAudioManager::PlayMenuTransitionSound()
{
    if (MenuTransitionSound)
    {
        UGameplayStatics::PlaySound2D(this, MenuTransitionSound);
    }
}

// Play notification sound based on message type
void AUIAudioManager::PlayNotificationSound(EMessageType MessageType)
{
    USoundCue* SelectedSound = nullptr;

    switch (MessageType)
    {
    case EMessageType::Success:
        SelectedSound = SuccessNotificationSound;
        break;
    case EMessageType::Error:
        SelectedSound = ErrorNotificationSound;
        break;
    case EMessageType::Warning:
        SelectedSound = WarningNotificationSound;
        break;
    default:
        break;
    }

    if (SelectedSound)
    {
        UGameplayStatics::PlaySound2D(this, SelectedSound);
    }
}

// Play in-game alert sound based on alert type
void AUIAudioManager::PlayInGameAlertSound(EAlertType AlertType)
{
    USoundCue* SelectedSound = nullptr;

    switch (AlertType)
    {
    case EAlertType::RadarWarning:
        SelectedSound = RadarAlertSound;
        break;
    case EAlertType::DamageWarning:
        SelectedSound = DamageAlertSound;
        break;
    case EAlertType::ObjectiveUpdate:
        SelectedSound = ObjectiveAlertSound;
        break;
    default:
        break;
    }

    if (SelectedSound)
    {
        UGameplayStatics::PlaySound2D(this, SelectedSound);
    }
}