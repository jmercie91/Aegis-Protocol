#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LegConfiguration.h"
#include "MechCharacter.generated.h"

UCLASS()
class AEGISPROTOCOL_API AMechCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMechCharacter();

    virtual void Tick(float DeltaTime) override;

    void SetMechLegs(ELegType SelectedLegType);
    void TakeDamage(float DamageAmount);
    void AttachWeapon(AActor* NewWeapon);
    void DetachWeapon();
    void DisableRadar(float DisableDuration);
    void DisableHUD(float DisableDuration);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Mech Stats")
    float Health;

    UPROPERTY(EditAnywhere, Category = "Mech Stats")
    float MaxHealth;

    UPROPERTY(EditAnywhere, Category = "Mech Stats")
    float Speed;

    UPROPERTY(EditAnywhere, Category = "Mech Stats")
    float TurnRate;

    UPROPERTY(EditAnywhere, Category = "Mech Stats")
    float MaxWeight;

    UPROPERTY(EditAnywhere, Category = "Movement")
    ALegConfiguration* LegConfiguration;

    UPROPERTY(EditAnywhere, Category = "Weapons")
    AActor* EquippedWeapon;

    UPROPERTY(EditAnywhere, Category = "EMP Effects")
    bool bIsRadarDisabled;

    UPROPERTY(EditAnywhere, Category = "EMP Effects")
    bool bIsHUDDisabled;

    void RestoreRadar();
    void RestoreHUD();
};
